#include "Scene0.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>







Scene0::Scene0(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	player = new Player(Vec3(0.0f, 0.0f, 0.0f),
						Vec3(0.0f, 0.0f, 0.0f), 1.0f);
						 

}

Scene0::~Scene0(){

	delete player;

	SDL_DestroyRenderer(renderer);

}

bool Scene0::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	IMG_Init(IMG_INIT_PNG);
	SDL_Surface* playerImage = IMG_Load("");//loading the image file
	SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);//loading and rendering the images' texture

	if (playerTexture == nullptr) printf("%s\n", SDL_GetError());// classic null checks
	if (playerImage == nullptr)
	{
		std::cerr << "Can't open the image" << std::endl;
		return false;
	}
	else
	{
		Vec3 worldCoordsFromScreenCoords;

		worldCoordsFromScreenCoords.x = xAxis / static_cast<float>(w) * static_cast<float>(playerImage->w);

		worldCoordsFromScreenCoords.y = yAxis / static_cast<float>(h) * static_cast<float>(playerImage->h);

		worldCoordsFromScreenCoords.print();

		player->setTexture(playerTexture);
		player->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

		SDL_FreeSurface(playerImage);
	}


	return true;
}

void Scene0::OnDestroy() {}

void Scene0::Update(const float deltaTime) {
	player->Update(deltaTime);
}

void Scene0::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;
	
	SDL_QueryTexture(player->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * player->getPos();
	SDL_Rect square;

	square.x = static_cast<int>(screenCoords.x);

	square.y = static_cast<int>(screenCoords.y);

	square.w = w;

	square.h = h;

	SDL_RenderCopyEx(renderer, player->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

void Scene0::HandleEvents(const SDL_Event& sdlEvent)
{

	player->HandleEvents(sdlEvent);

}
