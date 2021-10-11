#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include <iostream>
#include "ItemPool.h"
#include "Map.h"
#include "Monster.h"
#include "Data.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
	itemPool.loadItems();
	map.loadRooms();
	monster = new Monster("Room1");
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

	currentScene = new Scene0(windowPtr->GetSDL_Window(), map.searchRoom("Room1"));
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
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

				//Test for room switching
				case SDL_SCANCODE_F2:
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Scene0(windowPtr->GetSDL_Window(), map.searchRoom("Room2"));
					currentScene->OnCreate();
					monster->Update();
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
	itemPool.On_Destroy();
	map.On_Destroy();
	delete monster;
}