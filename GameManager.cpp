#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include <iostream>
#include "ItemPool.h"
#include "Map.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	player = new Player(Vec3(0.0f, 0.0f, 0.0f),
						Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	ItemPool::loadItems();
	Map::loadRooms();
	
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 576;
	windowPtr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT);

	if (windowPtr == nullptr) {
		OnDestroy();
		return false;
	}
	if (windowPtr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Scene0(windowPtr->GetSDL_Window(), Map::searchRoom("Room2"));
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}
	
	if (player == nullptr) {
		OnDestroy();
		return false;
	}

	return true;
}

/// Here's the whole game
void GameManager::Run() {
	SDL_Event sdlEvent;
	timer->Start();
	while (isRunning) {

		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				isRunning = false;
			}
			else if (sdlEvent.type == SDL_KEYDOWN)
			{

				switch (sdlEvent.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;



				default:
					break;

				}

			}
			currentScene->HandleEvents(sdlEvent);
		}


		timer->UpdateFrameTicks();
		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		

		/// Keeep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (windowPtr) delete windowPtr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
	if (player) delete player;
	ItemPool::On_Destroy();
	Map::On_Destroy();
}