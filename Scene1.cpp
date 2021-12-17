#include "Scene1.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include "Room.h"
#include "Monster.h"
#include "Data.h"
#include "ImageTexture.h"
#include "Sounds.h"
#include <typeinfo>


Scene1::Scene1(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	menu = new Menu();


}

Scene1::~Scene1(){
	delete menu;
}

bool Scene1::OnCreate() {
	int w, h;
	float xAxis = 30.0f;
	float yAxis = 15.0f;
	SDL_GetWindowSize(window,&w,&h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = (ndc * ortho);
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	projMa = projectionMatrix;
	//Set images
	IMG_Init(IMG_INIT_PNG);

	mainMenu = new ImageTexture("HorrorSchool_MainMenu_1.png");
	if (!ImageTextureSetup(mainMenu))
	{
		return false;
	}
	playButton = new ImageTexture("PlayButton_2.png");
	if (!ImageTextureSetup(playButton))
	{
		return false;
	}
	quitButton = new ImageTexture("QuitButton_2.png");
	if (!ImageTextureSetup(quitButton))
	{
		return false;
	}
	//Set Sounds Music
	initSounds();
	loadMusic("audio/CrEEP.mp3");
	playMusic(1);
	return true;
}


	

bool Scene1::ImageTextureSetup(ImageTexture *target_) {

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


		Vec3 lrWorld = invProjectionMatrix * lowerRight;
		Vec3 worldCoordsFromScreenCoords = lrWorld - ulWorld;

		target_->setTexture(targetTexture);
		target_->setImageSizeWorldCoords(worldCoordsFromScreenCoords);

		SDL_FreeSurface(targetImage);

	}

	return true;
}

void Scene1::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void Scene1::Update(const float deltaTime) {

	menu->Update(deltaTime);

}

void Scene1::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;
	
	//menu background image render
	SDL_QueryTexture(mainMenu->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * (Vec3(3.25f, -3.5f, 0.0f));
	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w - 100;
	square.h = h - 100;
	SDL_RenderCopyEx(renderer, mainMenu->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	//button image render, jk its actually magically the collision box or is it?
	SDL_QueryTexture(playButton->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * (Vec3(0.95f, -0.95f, 0.0f));
	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w;
	square.h = h;
	SDL_RenderCopyEx(renderer, playButton->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	SDL_QueryTexture(quitButton->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * (Vec3(0.95f, -8.0f, 0.0f));
	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w;
	square.h = h;
	SDL_RenderCopyEx(renderer, quitButton->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& sdlEvent)
{
	
	menu->HandleEvents(sdlEvent);
}





