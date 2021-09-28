#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include <vector>
#include "FileLoader.h"
#include "ItemPool.h"
#include <string.h>

using namespace std;




Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player = new Player(Vec3(0.0f, 0.0f, 0.0f),
					    Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	//flappybird = new GameObject("flappy");
						 
	//fileLoader = new FileLoader();
	//fileLoader->loadRoom("test");
	//flappybird = fileLoader->loadGameObject("flappy");

	flappybird = ItemPool::searchItem("flappy");
}

Scene0::~Scene0(){

	delete player;
	delete flappybird;
	delete fileLoader;
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
		//printf("player width: %f\n", worldCoordsFromScreenCoords.x);
		//printf("player height: %f\n", worldCoordsFromScreenCoords.y);

		SDL_FreeSurface(playerImage);
	}
	string image = "image/";
	image.append(flappybird->getimageName());
	SDL_Surface* flappyImage = IMG_Load(image.c_str());//loading the image file
	SDL_Texture* flappyTexture = SDL_CreateTextureFromSurface(renderer, flappyImage);//loading and rendering the images' texture


	if (flappyTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
	if (flappyImage == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{

		Vec3 upperLeft(0.0f, 0.0f, 0.0f);
		Vec3 lowerRight(static_cast<float>(flappyImage->w), static_cast<float>(flappyImage->h), 0.0f);
		Vec3 ulWorld = invProjectionMatrix * upperLeft;
		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;

		flappybird->setTexture(flappyTexture);
		flappybird->setImageSizeWorldCoords(worldCoordsFromScreenCoords);
		//printf("flappy width: %f\n", worldCoordsFromScreenCoords.x);
		//printf("flappy height: %f\n", worldCoordsFromScreenCoords.y);

		SDL_FreeSurface(flappyImage);
	}


	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float deltaTime) {
	player->Update(deltaTime);
	
	//if (Physics::CollisionDetect(*player, *flappybird))
	//	printf("collide\n");
	//else
	//	printf("not collide\n");
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

	square.x = static_cast<int> (screenCoords.x);
	square.y = static_cast<int> (screenCoords.y);
	square.w = w;
	square.h = h;

	SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	//render flappybird
	SDL_QueryTexture(flappybird->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * flappybird->getPos();

	square.x = static_cast<int> (screenCoords.x);
	square.y = static_cast<int> (screenCoords.y);
	square.w = w;
	square.h = h;

	SDL_RenderCopyEx(renderer, flappybird->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{

	player->PlayerController(sdlEvent);

}
