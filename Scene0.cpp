#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include "Room.h"
#include "Monster.h"
#include "Data.h"

#define WORLD_W 1500
#define WORLD_H 900

Scene0::Scene0(SDL_Window* sdlWindow_, Room *room_): room(room_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	cout << room->getName() << endl;
	cout << "Monster location: " << monster->getCurrRoom() << endl;

}

Scene0::~Scene0(){
	delete room;
}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = (ndc * ortho);
	invProjectionMatrix = MMath::inverse(projectionMatrix);

	//Set images
	IMG_Init(IMG_INIT_PNG);
	string image = "image/";
	image.append(room->getimageName());
	roomImage = IMG_Load(image.c_str());//loading the image file
	roomTexture = SDL_CreateTextureFromSurface(renderer, roomImage);//loading and rendering the images' texture
	if (roomTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
	if (roomImage == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{

		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 lowerRight(static_cast<float>(roomImage->w), static_cast<float>(roomImage->h), 0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		worldSizeScreenCoords = lrWorld - ulWorld;

		//player->setTexture(roomTexture);
		//player->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

		SDL_FreeSurface(roomImage);
	}

	SDL_Surface* playerImage = IMG_Load("image/TestPlayer.png");//loading the image file
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);//loading and rendering the images' texture
	if (playerTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
	if (playerImage == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{
		
		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 lowerRight(static_cast<float>(playerImage->w), static_cast<float>(playerImage->h), 0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;

		player->setTexture(playerTexture);
		player->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

		SDL_FreeSurface(playerImage);
	}

	//Set images for all the item
	for (GameObject *item : room->getItemList()) {

		string image = "image/";
		image.append(item->getimageName());
		SDL_Surface* itemImage = IMG_Load(image.c_str());//loading the image file
		SDL_Texture* itemTexture = SDL_CreateTextureFromSurface(renderer, itemImage);//loading and rendering the images' texture

		if (itemTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
		if (itemImage == nullptr)
		{
			std::cerr << "Can't open the image" << std::endl;
			return false;
		}
		else
		{

			Vec3 upperLeft(0.0f, 0.0f, 0.0f);
			Vec3 lowerRight(static_cast<float>(itemImage->w), static_cast<float>(itemImage->h), 0.0f);
			Vec3 ulWorld = invProjectionMatrix * upperLeft;
			Vec3 lrWorld = invProjectionMatrix * lowerRight;
			Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;

			item->setTexture(itemTexture);
			item->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

			SDL_FreeSurface(itemImage);
		}
	}

	lightImage = IMG_Load("image/FakeLight.png");//loading the image file
	lightTexture = SDL_CreateTextureFromSurface(renderer, lightImage);//loading and rendering the images' texture
	if (lightTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
	if (lightImage == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{
		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 lowerRight(static_cast<float>(lightImage->w), static_cast<float>(lightImage->h), 0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		worldSizeScreenCoords = lrWorld - ulWorld;


		SDL_SetTextureBlendMode(lightTexture, SDL_BLENDMODE_MOD);
		SDL_SetTextureAlphaMod(lightTexture, 251);

		SDL_FreeSurface(lightImage);
	}


	return true;
}

void Scene0::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void Scene0::Update(const float deltaTime) {


	//Physics::SimpleNewtonMotion(*player, deltaTime);

	for (GameObject* item : room->getItemList()) {
		if (Physics::CollisionDetect(*player, *item, deltaTime)) {
			//cout << "collide with " << item->getName() << endl;
			//cout << item->getName();
			//printf("%f, %f\n", item->getPos().x, item->getPos().y);
			//cout << player->getName();
			//printf("%f, %f\n", player->getPos().x, player->getPos().y);
			player->setCollide(true);
		}
	}

	player->Update(deltaTime);
//	printf("%f, %f\n", player->getPos().x, player->getPos().y);


	projectionMatrix = MMath::translate(Vec3(-player->getVel().x, player->getVel().y, 0.0f) * 0.5f) * projectionMatrix;

	//Get camera location
	Vec3 projectionLoc = projectionMatrix.getColumn(3);

	//Set camera bounds
	if (projectionLoc.x > WORLD_W / 2) {

		projectionLoc.x = WORLD_W / 2;
		projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[2],
			projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
			projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
			projectionLoc.x, projectionMatrix[13], projectionMatrix[14], projectionMatrix[15]);

		cout << "Reach bounds on left" << endl;

	} 	if (projectionLoc.y > WORLD_H / 2) {
		
		projectionLoc.y = WORLD_H / 2;
		projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[2],
			projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
			projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
			projectionMatrix[12], projectionLoc.y, projectionMatrix[14], projectionMatrix[15]);
				
		cout << "Reach bounds on Top" << endl;
	}
	if (projectionLoc.x < WORLD_W / 4) {
		projectionLoc.x = WORLD_W / 4;
		projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[2],
			projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
			projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
			projectionLoc.x, projectionMatrix[13], projectionMatrix[14], projectionMatrix[15]);
		cout << "Reach bounds on right" << endl;
	}
	if (projectionLoc.y < WORLD_H / 4) {

		projectionLoc.y = WORLD_H / 4;
		projectionMatrix = Matrix4(projectionMatrix[0], projectionMatrix[1], projectionMatrix[2], projectionMatrix[2],
			projectionMatrix[4], projectionMatrix[5], projectionMatrix[6], projectionMatrix[7],
			projectionMatrix[8], projectionMatrix[9], projectionMatrix[10], projectionMatrix[11],
			projectionMatrix[12], projectionLoc.y, projectionMatrix[14], projectionMatrix[15]);

		cout << "Reach bounds on bot" << endl;
	}


}

void Scene0::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;
	//projectionMatrix = MMath::translate(player->getPos() - Vec3(camera.x, camera.y, 0.0f)) * projectionMatrix;

	//Room render
	SDL_QueryTexture(roomTexture, nullptr, nullptr, &w, &h);

	screenCoords = projectionMatrix * (Vec3(0.0f, 0.0f, 0.0f));
	square.x = static_cast<int> (screenCoords.x - WORLD_W /2);
	square.y = static_cast<int> (screenCoords.y - WORLD_H /2);
	square.w = WORLD_W;
	square.h = WORLD_H;

	SDL_RenderCopyEx(renderer, roomTexture, nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	//Player render
	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * player->getPos();
	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w;
	square.h = h;

	SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	// Objects render
	for (GameObject *item : room->getItemList()) {

		SDL_QueryTexture(item->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * (item->getPos());
		square.x = static_cast<int> (screenCoords.x - w / 2);
		square.y = static_cast<int> (screenCoords.y - h / 2);
		square.w = w;
		square.h = h;

		SDL_RenderCopyEx(renderer, item->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);
	}


	//Light Render
	SDL_QueryTexture(lightTexture, nullptr, nullptr, &w, &h);

	screenCoords = projectionMatrix * player->getPos();
	square.x = static_cast<int> (screenCoords.x - w/2 * 2);
	square.y = static_cast<int> (screenCoords.y - h/2 * 3);
	square.w = w * 2;
	square.h = h * 3;

	SDL_RenderCopyEx(renderer, lightTexture, nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{

	player->PlayerController(sdlEvent);

}


