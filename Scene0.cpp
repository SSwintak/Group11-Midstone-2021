#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include "FileLoader.h"
#include "Room.h"



Scene0::Scene0(SDL_Window* sdlWindow_, Room *room_): room(room_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	

	cout << room->getName();

}

Scene0::~Scene0(){

	
	delete room;
	SDL_DestroyRenderer(renderer);

}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 15.0f;
	float yAxis = 7.5f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);

	//Set images
	IMG_Init(IMG_INIT_PNG);
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

void Scene0::OnDestroy() {}

void Scene0::Update(const float deltaTime) {
	player->Update(deltaTime);

	
	for (GameObject* item : room->getItemList()) {
		if (Physics::CollisionDetect(*player, *item)) {
			cout << "collide with " << item->getName() << endl;
			cout << item->getName();
			printf ("%f, %f\n", item->getPos().x, item->getPos().y);
			cout << player->getName();
			printf("%f, %f\n", player->getPos().x, GameManager::player->getPos().y);
		}

		//else
		//	printf("not collide\n");
	}
	
	

}

void Scene0::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;
	
	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * player->getPos();

	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w;
	square.h = h;

	SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	// 
	for (GameObject *item : room->getItemList()) {

		SDL_QueryTexture(item->getTexture(), nullptr, nullptr, &w, &h);
		screenCoords = projectionMatrix * item->getPos();

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


