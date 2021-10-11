#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include "FileLoader.h"
#include "Room.h"
#include "Monster.h"
#include "Data.h"

#define WORLD_W 1500
#define WORLD_H 800

Scene0::Scene0(SDL_Window* sdlWindow_, Room *room_): room(room_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player = new Player(Vec3(0.0f, 0.0f, 0.0f),
					    Vec3(0.0f, 0.0f, 0.0f), 1.0f);

	cout << room->getName() << endl;
	cout << "Monster location: " << monster->getCurrRoom() << endl;


}

Scene0::~Scene0(){
	delete player;
	delete room;
}

bool Scene0::OnCreate() {
	int w, h;
	xAxis = 30.0f;
	yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);
	camera = { 0, 0, static_cast<int>(xAxis), static_cast<int>(yAxis) };

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = (ndc * ortho);
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	worldSize = invProjectionMatrix * Vec3(WORLD_W, WORLD_H, 0.0f);
	worldSize = Vec3(abs(worldSize.x), abs(worldSize.y), 0.0f);

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


	return true;
}

void Scene0::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void Scene0::Update(const float deltaTime) {
	player->Update(deltaTime);
	
	//for (GameObject* item : room->getItemList()) {
	//	if (Physics::CollisionDetect(*player, *item)) {
	//		cout << "collide with " << item->getName() << endl;
	//		cout << item->getName();
	//		printf ("%f, %f\n", item->getPos().x, item->getPos().y);
	//		cout << player->getName();
	//		printf("%f, %f\n", player->getPos().x, player->getPos().y);
	//	}

	//	//else
	//	//	printf("not collide\n");
	//}

	camera.x = (player->getPos().x + player->getImageSizeWorldCoords().x/2) ;
	camera.y = (player->getPos().y + player->getImageSizeWorldCoords().y/2);


	
	/*
	* WorldSize / 2 = Half of the image size
	* Since the camera starts from the centre of the screen, divide half again
	* therefore, worldsize / 4
	*/
	if (camera.x < -worldSize.x / 4) {
		camera.x = -worldSize.x / 4;
		cout << "Reach bounds on left" << endl;
	}
	if (camera.y < -worldSize.y / 4) {
		camera.y = -worldSize.y / 4;
		cout << "Reach bounds on bot" << endl;
	}
	if (camera.x > worldSize.x / 4) {
		camera.x = worldSize.x / 4;
		cout << "Reach bounds on right" << endl;
	}
	if (camera.y > worldSize.y / 4) {
		camera.y = worldSize.y / 4;
		cout << "Reach bounds on bot" << endl;
	}



	cout << camera.x << endl;
}

void Scene0::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;

	//Room render
	SDL_QueryTexture(roomTexture, nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * (Vec3(0.0f, 0.0f, 0.0f) - Vec3(camera.x, camera.y, 0.0f));

//	screenCoords = projectionMatrix * (Vec3(-worldSize.x/2, -worldSize.y/2, 0.0f) - Vec3(camera.x, camera.y, 0.0f));
	square.x = static_cast<int> (screenCoords.x - WORLD_W /2);
	square.y = static_cast<int> (screenCoords.y - WORLD_H /2);
	square.w = WORLD_W;
	square.h = WORLD_H;

	SDL_RenderCopyEx(renderer, roomTexture, nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	//Player render
	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * (player->getPos());
	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w;
	square.h = h;

	SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	// 
	for (GameObject *item : room->getItemList()) {

		SDL_QueryTexture(item->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * (item->getPos() - Vec3(camera.x, camera.y, 0.0f));

		square.x = static_cast<int> (screenCoords.x - w / 2);
		square.y = static_cast<int> (screenCoords.y - h / 2);
		square.w = w;
		square.h = h;

		SDL_RenderCopyEx(renderer, item->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);
	}


	SDL_RenderPresent(renderer);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{

	player->PlayerController(sdlEvent);

}
