#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Text.h"
#include <iostream>
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include "Room.h"
#include "Monster.h"
#include "Data.h"
#include "ImageTexture.h"
#include "Itempool.h"
#include <typeinfo>


//#define WORLD_W 1280
//#define roomHeight 720

Scene0::Scene0(SDL_Window* sdlWindow_, Room *room_): room(room_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	cout << "--------------------------------------" << endl;
	cout << room->getName() << endl;
	cout << "--------------------------------------" << endl;
	roomHeight = room->getHeight();
	roomWidth = room->getWidth();
	timeCount = 0;
	camera = true;
	if (monster->getRoom() == room->getName() && monster->getState() != TInactive) {
		monsterExist = true;
		//cout << monster->getState();
	}
	else {
		monsterExist = false;
	}
	itemName = nullptr;
	message = " ";
	message = "Entering " + room->getName();
	timeDelay = 0.0f;
}

Scene0::~Scene0(){
	delete room;
	delete itemName;
}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(roomWidth, roomHeight);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = (ndc * ortho);
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	projMa = projectionMatrix;
	//Set font
	TTF_Init();

	initFonts();

	//Set images
	IMG_Init(IMG_INIT_PNG);

	//Set room images
	if (!ImageTextureSetup(room, false)) {
		return false;
	}
	//Set door images
	for (Door* door : room->getConnectedRooms()) {
		if (!ImageTextureSetup(door, false)) {
			return false;
		}
	}
	//Set player images
	if (!ImageTextureSetup(player, true)) {
		return false;
	}
	//Set Monster Images
	//if (monsterExist) {
		//if (!ImageTextureSetup(monster, false)) {
		//	return false;
		//}
		string image = "image/";
		image.append(monster->getimageName());
		SDL_Surface* targetImage = IMG_Load(image.c_str());//loading the image file
		SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, targetImage);//loading and rendering the images' texture
		if (targetTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
		if (targetImage == nullptr)
		{
			std::cerr << "Can't open the image" << monster->getimageName() << std::endl;
			return false;
		}
		else
		{
			Vec3 upperLeft(0.0f, 0.0f, 0.0f);
			Vec3 ulWorld = invProjectionMatrix * upperLeft;
			Vec3 lowerRight = Vec3(146.0f, 294.0f, 0.0f);
			Vec3 lrWorld = invProjectionMatrix * lowerRight;
			Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;
			monster->setTexture(targetTexture);
			monster->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
			SDL_FreeSurface(targetImage);
		}
	//}

	//Set images for all the item
	for (GameObject *item : room->getItemList()) {
		if (!ImageTextureSetup(item, false)) {
			return false;
		}
	}

	//Set Light images
	light = new ImageTexture("FakeLight.png");
	if (!ImageTextureSetup(light, false)) {
		return false;
	}
	//Set dead scene
	//deadScene = new ImageTexture("HorrorSchool_DeathScreen_1.png");
	//if (!ImageTextureSetup(deadScene, false)) {
	//	return false;
	//}
	if (player->getPrevRoom() != "Custodian" && room->getName() == "Hallway") {
		projectionMatrix = player->getCameraHallway();
	}
	else if (player->getPrevRoom() != "Hallway" && room->getName() == "SecondFloor") {
		projectionMatrix = player->getCameraSecondFloor();
	}

	//Set HUD Image
	playerHUD = new ImageTexture("HorrorSchool_UI_HUD_1.png");
	if (!ImageTextureSetup(playerHUD, false)) {
		return false;
	}


	//Set images for inventory items
	for (string itemName : player->getInventory()) {
		GameObject* item = itemPool.searchItem(itemName);
		if (!ImageTextureSetup(item, false)) {
			return false;
		}
	}


	////set UI Item Image(s)
	//items[0] = new ImageTexture("CrowBar_Icon_1.png");
	//if (!ImageTextureSetup(items[0], false)) {
	//	return false;
	//}

	//items[1] = new ImageTexture("CrowBar_1.png");
	//if (!ImageTextureSetup(items[1], false)) {
	//	return false;
	//}

	//items[2] = new ImageTexture("Keys&Tag_Icon_1.png");
	//if (!ImageTextureSetup(items[2], false)) {
	//	return false;
	//}

	//items[3] = new ImageTexture("Lighter_Icon_1.png");
	//if (!ImageTextureSetup(items[3], false)) {
	//	return false;
	//}

	//items[4] = new ImageTexture("Shoe_1.png");
	//if (!ImageTextureSetup(items[4], false)) {
	//	return false;
	//}

	//items[5] = new ImageTexture("StickyNote_Icon_1.png");
	//if (!ImageTextureSetup(items[5], false)) {
	//	return false;
	//}

	//items[6] = new ImageTexture("PoliceDoc_Icon_1.png");
	//if (!ImageTextureSetup(items[6], false)) {
	//	return false;
	//}

	//items[7] = new ImageTexture("Fuse_Icon_1.png");
	//if (!ImageTextureSetup(items[7], false)) {
	//	return false;
	//}

	

	return true;
}




bool Scene0::ImageTextureSetup(ImageTexture *target_, bool animate) {
	string image = "image/";
	image.append(target_->getimageName());
	SDL_Surface* targetImage = IMG_Load(image.c_str());//loading the image file
	SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, targetImage);//loading and rendering the images' texture
	if (targetTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
	if (targetImage == nullptr)
	{
		std::cerr << "Can't open the image" << target_->getimageName() << std::endl;
		return false;
	}
	else
	{

		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lowerRight(static_cast<float>(targetImage->w), static_cast<float>(targetImage->h), 0.0f);
		if (animate) {

			lowerRight = Vec3(82.0f, 273.0f, 0.0f);
			//cout << "is gameobject" << endl;
		}
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;

		target_->setTexture(targetTexture);
		target_->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

		SDL_FreeSurface(targetImage);
	}

	if (monsterExist)
	{
		string image = "image/";
		image.append(monster->getimageName());
		SDL_Surface* targetImage = IMG_Load(image.c_str());//loading the image file
		SDL_Texture* targetTexture = SDL_CreateTextureFromSurface(renderer, targetImage);//loading and rendering the images' texture
		if (targetTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
		if (targetImage == nullptr)
		{
			std::cerr << "Can't open the image" << monster->getimageName() << std::endl;
			return false;
		}
		else
		{

			Vec3 upperLeft(0.0f, 0.0f, 0.0f);
			Vec3 ulWorld = invProjectionMatrix * upperLeft;
			Vec3 lowerRight = Vec3(100.0f, 200.0f, 0.0f);

			Vec3 lrWorld = invProjectionMatrix * lowerRight;
			Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;

			monster->setTexture(targetTexture);
			monster->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

			SDL_FreeSurface(targetImage);
		}
	}


	return true;
}

void Scene0::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void Scene0::Update(const float deltaTime) {

	//Time count
	timeDelay += deltaTime;

	if (monster->getRoom() == room->getName() 
		&& monster->getState() != TInactive
		&& monster->getState() != TRoomSwitch) {
		monsterExist = true;
	}


	if (timeCount >= 3.0f && (monster->getState() == TRoomSwitch)) {
		monster->setState(THunt);
	}

	//Player Object collision
	for (GameObject* item : room->getItemList()) {
		if (item->getType() == TStaticObject) {
			if (Physics::CollisionDetect(*player, *item)) {
				player->setCollide(true);
			}
		}
	}

	//Monster checks
	if (monsterExist 
		&& (monster->getState() != TRoomSwitch)
		&& (monster->getState() != TInactive)) {
		if (Physics::InteractionDetect(*player, *monster)) {
			//cout << monster->getState();
			//cout << "Switch to Hunt" << endl;
			if (monster->getState() != THunt) monster->setState(THunt);
		}
		if (Physics::CollisionDetect(*player, *monster)) {
			//player dead
			monster->setVel(Vec3(0.0f, 0.0f, 0.0f));
			monster->setState(TInactive);
			player->setAlive(false);
		}

	}

	if (player->getAlive()) {
		monster->Update(deltaTime);
		player->Update(deltaTime);
	}

	timeCount += deltaTime;

	//Player boundaries

	Vec3 playerWorld = player->getPos();

	playerWorld.x += abs(player->getImageSizeWorldCoords().x) / 2;
	playerWorld.y += abs(player->getImageSizeWorldCoords().y) / 2;
	playerWorld = projMa * playerWorld;

	//Right
	if (playerWorld.x >= roomWidth) {
		player->setCollide(true);
		cout << "player reach right room edge" << endl;
	}
	//Top
	if (playerWorld.y <= 0.0f) {
		player->setCollide(true);
		cout << "player reach left room edge" << endl;
	}

	playerWorld = player->getPos();
	playerWorld.x -= abs(player->getImageSizeWorldCoords().x) / 2;
	playerWorld.y -= abs(player->getImageSizeWorldCoords().y) / 2;
	playerWorld = projMa * playerWorld;
	//Left
	if (playerWorld.x <= 0.0f) {
		player->setCollide(true);
		cout << "player reach right room edge" << endl;
	}
	//Bot
	if (playerWorld.y >= roomHeight) {
		player->setCollide(true);
		cout << "player reach left room edge" << endl;
	}


	/*Stupid camera that I will come fix later (Right, Bot boundaries)*/
	//Move camera along with the player
	if (camera) {
		float cameraSpeed = 0.5f;

		if (roomWidth > 1280) {
			cameraSpeed = 0.5f;
		}


		projectionMatrix = MMath::translate(Vec3(-player->getVel().x, player->getVel().y, 0.0f) * cameraSpeed) * projectionMatrix;

		//Get camera location
		projectionLoc = projectionMatrix.getColumn(3);
		//Set camera bounds
		if (projectionLoc.x > roomWidth / 2) {

			projectionLoc.x = roomWidth / 2;
			projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[3],
				projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
				projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
				projectionLoc.x, projectionMatrix[13], projectionMatrix[14], projectionMatrix[15]);

			//cout << "Reach bounds on left" << endl;

		}
		if (projectionLoc.y > roomHeight / 2) {

			projectionLoc.y = roomHeight / 2;
			projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[3],
				projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
				projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
				projectionMatrix[12], projectionLoc.y, projectionMatrix[14], projectionMatrix[15]);

			//cout << "Reach bounds on Top" << endl;
		}
		float rightEdge = roomWidth / 3.345;
		if (roomWidth >= 2560) {
			rightEdge = 0.0f;
		}

		if (projectionLoc.x < rightEdge) {
			projectionLoc.x = rightEdge;
			projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[3],
				projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
				projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
				projectionLoc.x, projectionMatrix[13], projectionMatrix[14], projectionMatrix[15]);
			//cout << "Reach bounds on right" << endl;
		}
		if (projectionLoc.y < roomHeight / 3.345) {
			projectionLoc.y = roomHeight / 3.345;
			projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[3],
				projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
				projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
				projectionMatrix[12], projectionLoc.y, projectionMatrix[14], projectionMatrix[15]);

			//cout << "Reach bounds on bot" << endl;
		}
	}
	if (projectionLoc.y < roomHeight / 3.345) {
		projectionLoc.y = roomHeight / 3.345;
		projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[3],
								   projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
								   projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
								   projectionMatrix[12],   projectionLoc.y,  projectionMatrix[14], projectionMatrix[15]);

		//cout << "Reach bounds on bot" << endl;
	}

	//projectionMatrix.print();


}

void Scene0::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	SDL_Rect dstRect;
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;

	if (player->getAlive()) {

		//Room render
		SDL_QueryTexture(room->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * (Vec3(0.0f, 0.0f, 0.0f));
		square.x = static_cast<int> (screenCoords.x - roomWidth / 2);
		square.y = static_cast<int> (screenCoords.y - roomHeight / 2);
		square.w = roomWidth;
		square.h = roomHeight;
		SDL_RenderCopyEx(renderer, room->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);
		// Objects render
		for (GameObject* item : room->getItemList()) {
			SDL_QueryTexture(item->getTexture(), nullptr, nullptr, &w, &h);
			screenCoords = projectionMatrix * (item->getPos());
			square.x = static_cast<int> (screenCoords.x - w / 2);
			square.y = static_cast<int> (screenCoords.y - h / 2);
			square.w = w;
			square.h = h;
			SDL_RenderCopyEx(renderer, item->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);
		}
		//Door Render
		for (Door* door : room->getConnectedRooms()) {
			SDL_QueryTexture(door->getTexture(), nullptr, nullptr, &w, &h);
			screenCoords = projectionMatrix * (door->getPos());
			square.x = static_cast<int> (screenCoords.x - w / 2);
			square.y = static_cast<int> (screenCoords.y - h / 2);
			square.w = w;
			square.h = h;
			SDL_RenderCopyEx(renderer, door->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);
		}
		//Player render
		if (player->getIsMoving() == true)
		{

			int totalFrames = 7;
			int delayPerFrame = 100;
			float spriteOffset = 10;//only use if there is an offset in the sprite sheet
			SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
			screenCoords = projectionMatrix * player->getPos();
			square.x = 0;
			square.y = 0;
			square.w = 82;
			square.h = 273;

			dstRect.x = static_cast<int> (screenCoords.x - 82 / 2);
			dstRect.y = static_cast<int> (screenCoords.y - 273 / 2);
			dstRect.w = 82;
			dstRect.h = 273;

			int frame = (static_cast<int>(SDL_GetTicks() / delayPerFrame) % totalFrames);
			square.x = frame * (square.w + spriteOffset);//spriteOffset, added because there is an offset in the player sprite sheet

			SDL_RenderCopyEx(renderer, player->getTexture(), &square, &dstRect, rot, nullptr, player->getFlip());
		}
		else
		{

			SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
			screenCoords = projectionMatrix * player->getPos();
			square.x = 0;
			square.y = 0;
			square.w = 82;
			square.h = 273;

			dstRect.x = static_cast<int> (screenCoords.x - 82 / 2);
			dstRect.y = static_cast<int> (screenCoords.y - 273 / 2);
			dstRect.w = 82;
			dstRect.h = 273;

			SDL_RenderCopyEx(renderer, player->getTexture(), &square, &dstRect, rot, nullptr, player->getFlip());
		}

		//Monster Render
		if (monsterExist
			&& (monster->getState() != TRoomSwitch)
			&& (monster->getState() != TInactive)) {

			if (monster->getIsMoving() == true)
			{

				int totalFrames2 = 8;
				int delayPerFrame2 = 90;
				float spriteOffset2 = 10;//only use if there is an offset in the sprite sheet
				SDL_QueryTexture(monster->getTexture(), nullptr, nullptr, &w, &h);
				screenCoords = projectionMatrix * monster->getPos();
				square.x = 0;
				square.y = 0;
				square.w = 146;
				square.h = 294;

				dstRect.x = static_cast<int> (screenCoords.x - 146 / 2);
				dstRect.y = static_cast<int> (screenCoords.y - 294 / 2);
				dstRect.w = 146;
				dstRect.h = 294;

				int frame2 = (static_cast<int>(SDL_GetTicks() / delayPerFrame2) % totalFrames2);
				square.x = frame2 * (square.w + spriteOffset2);//spriteOffset, added because there is an offset in the player sprite sheet

				SDL_RenderCopyEx(renderer, monster->getTexture(), &square, &dstRect, rot, nullptr, monster->getFlip());

			}
			else
			{
				SDL_QueryTexture(monster->getTexture(), nullptr, nullptr, &w, &h);
				screenCoords = projectionMatrix * monster->getPos();
				square.x = 0;
				square.y = 0;
				square.w = 146;
				square.h = 294;

				dstRect.x = static_cast<int> (screenCoords.x - 146 / 2);
				dstRect.y = static_cast<int> (screenCoords.y - 294 / 2);
				dstRect.w = 146;
				dstRect.h = 294;

				SDL_RenderCopyEx(renderer, monster->getTexture(), &square, &dstRect, rot, nullptr, monster->getFlip());
			}

		}
		//Light Render
		SDL_QueryTexture(light->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * player->getPos();
		square.x = static_cast<int> (screenCoords.x - w / 2 * 4);
		square.y = static_cast<int> (screenCoords.y - h / 2 * 4);
		square.w = w * 4;
		square.h = h * 4;
		SDL_SetTextureBlendMode(light->getTexture(), SDL_BLENDMODE_MOD);
		SDL_SetTextureAlphaMod(light->getTexture(), 251);
		SDL_RenderCopyEx(renderer, light->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

		//UI HUD Render
		SDL_QueryTexture(playerHUD->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = Vec3(510.0f, 50.0f, 0.0f);
		square.x = static_cast<int> (screenCoords.x - w / 2);
		square.y = static_cast<int> (screenCoords.y - h / 2);
		square.w = w;
		square.h = h;

		SDL_RenderCopyEx(renderer, playerHUD->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

		//UI Items Render
		if (player->getHasItem())
		{
			//Set images for inventory items
			vector<string> playerInventory = player->getInventory();
			for (int i = 0; i < playerInventory.size(); i++) {
				GameObject* item = itemPool.searchItem(playerInventory[i]);
				float xPosition = 250.0f + (i * 65);
				SDL_QueryTexture(item->getTexture(), nullptr, nullptr, &w, &h);
				screenCoords = Vec3(xPosition, 50.0f, 0.0f);
				square.x = static_cast<int> (screenCoords.x - w / 2);
				square.y = static_cast<int> (screenCoords.y - h / 2);
				square.w = w;
				square.h = h;
				//itemPool.searchItem("CrowBar")->getTexture();
				SDL_RenderCopyEx(renderer, item->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);
			}
		}

		//Draw text on screen
		if (message != " ") {
			if (drawText(renderer, message.c_str(), 100, 500, 0, 0, 0, 0)) {
				if (timeDelay >= 2.0f) {
					message = " ";
				}
			}
		}
	}

	SDL_RenderPresent(renderer);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{
	
	if (player->getAlive()) {
		player->PlayerController(sdlEvent);
		//Interaction with items
		for (GameObject* item : room->getItemList()) {
			if (Physics::InteractionDetect(*player, *item)) {
				bool interactSuccess = player->interactObject(sdlEvent, item);
				if (interactSuccess && item->getType() == TPickable) {
					message = item->getDescription();
					timeDelay = 0.0f;
					room->removeItem(item->getName());
				}
				else if (interactSuccess && item->getType() == TInteractable) {
					if (interactSuccess) {
						if (item->getName() == "FuseBox") {
							message = "You activate the fuse box";
							timeDelay = 0.0f;
						}
					}
					else {
						if (item->getName() == "FuseBox") {
							message = "Key Required: " + item->getRequiredKey();
							timeDelay = 0.0f;
						}
					}
				}
			
			}
		}

		//Door Interaction
		for (Door* door : room->getConnectedRooms()) {
			if (Physics::InteractionDetect(*player, *door)) {
				//If interacting with the door
				if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {
					//Switch room if the door is not locked
					//else check the required key
					if (door->getLocked()) {
						string requiredKey = door->getRequiredKey();

						if (player->searchInventory(requiredKey)) {
							player->switchRoom(door->getConnectedRoom());
							if (room->getName() == "Hallway")  {
								player->setCameraHallway(projectionMatrix);
							}
							else if (room->getName() == "SecondFloor") {
								player->setCameraSecondFloor(projectionMatrix);
							}
						}
						else {
							message = door->getDescription();
							timeDelay = 0.0f;
							door->displayDescription();
						}
					}
					else {
						player->switchRoom(door->getConnectedRoom());
						if (room->getName() == "Hallway") {
							player->setCameraHallway(projectionMatrix);
						}
						else if (room->getName() == "SecondFloor") {
							player->setCameraSecondFloor(projectionMatrix);
						}
					}

					//If monster is chasing the player
					if (monsterExist && monster->getState() == THunt) {
						//If the player's destinatination is not a safe room, keep hunting
						bool isSafe = monster->isSafeRoom(player->getRoom());
						if (!isSafe) {
							cout << "Not Safe" << endl;
							monster->setState(TRoomSwitch);
							cout << "Monster room switch" << endl;
							timeCount = 0;
							monster->switchRoom(player->getRoom());
						}
						else if (isSafe) {
							player->setProgress(GStaffRoom);
						}
					}
				}
			}
		}
	}

}
