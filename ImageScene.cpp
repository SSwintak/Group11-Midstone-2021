#include "ImageScene.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Text.h"
#include "Player.h"
#include "GameObject.h"
#include "Physics.h"
#include "Data.h"
#include "ImageTexture.h"
#include <typeinfo>


//#define WORLD_W 1280
//#define roomHeight 720

ImageScene::ImageScene(SDL_Window* sdlWindow_){
	window = sdlWindow_;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

ImageScene::~ImageScene(){
}

bool ImageScene::OnCreate() {
	int w, h;
	float xAxis = 15.0f;
	float yAxis = 7.5f;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(-xAxis, xAxis, -yAxis, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	invProjectionMatrix = MMath::inverse(projectionMatrix);
	//Set images
	IMG_Init(IMG_INIT_PNG);

	//Set font
	TTF_Init();
	initFonts();

	//Set dead scene
	if (!player->getAlive()) {
		imageDisplayed = new ImageTexture("HorrorSchool_DeathScreen_1_576p.png");
	}
	//Set end scene
	else {
		imageDisplayed = new ImageTexture("End2.png");
	}
	if (!ImageTextureSetup(imageDisplayed)) {
		return false;
	}
	return true;
}



bool ImageScene::ImageTextureSetup(ImageTexture *target_) {
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

void ImageScene::OnDestroy() {
	SDL_DestroyRenderer(renderer);
}

void ImageScene::Update(const float deltaTime) {
}

void ImageScene::Render() {

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect square;
	Vec3 screenCoords;
	int w, h;
	static double rot = 0.0f;
	//Dislay image
	SDL_GetWindowSize(window, &w, &h);
	SDL_QueryTexture(imageDisplayed->getTexture(), nullptr, nullptr, &w, &h);
	screenCoords = projectionMatrix * Vec3(0.0f, 0.0f, 0.0f);
	square.x = static_cast<int> (screenCoords.x - w / 2);
	square.y = static_cast<int> (screenCoords.y - h / 2);
	square.w = w;
	square.h = h;
	SDL_RenderCopyEx(renderer, imageDisplayed->getTexture(), nullptr, &square, rot, nullptr, SDL_FLIP_NONE);

	//Draw text on screen
	if (player->getEnd()) {
		drawText(renderer, "Press ESC to Quit Game", 350, 500, 0, 0, 0, 0);
	}
	else if (!player->getAlive()) {
		drawText(renderer, "Press Q to respawn to previous progress", 350, 500, 0, 0, 0, 0);
	}

	SDL_RenderPresent(renderer);
}

void ImageScene::HandleEvents(const SDL_Event& sdlEvent){

}

Room* ImageScene::getRoom()
{
	return nullptr;
}





