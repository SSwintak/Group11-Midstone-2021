#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "ImageScene.h"
#include "Event.h"
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
	monster = new Monster();
	player = new Player(Vec3(-10.0f, 0.0f, 0.0f),
						Vec3(0.0f, 0.0f, 0.0f), 1.0f);
}


/// In this OnCreate() method, function, subroutine, whatever the word, 
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

	currentScene = new Scene0(windowPtr->GetSDL_Window(), map.searchRoom("Custodian"));
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

				case SDL_SCANCODE_F1:
					SceneSwitch("Custodian");
					break;

				case SDL_SCANCODE_Q:
					cout << player->getProgress() << endl;
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

		//Player switch room
		if (player->getWin()) {
			SceneSwitch("dead");
		}
		else if (player->getAlive()) {
			if (player->getRoom() != currentScene->getRoom()->getName()) {
				cout << "Room switching" << endl;
				SceneSwitch(player->getRoom());
			}
		}
		else if (!player->getAlive()) {
			SceneSwitch("dead");
		}

		//Monster Chase Part
		cout << "Player Pos: ";
		player->getPos().print();
		if (player->getProgress() == GFirstEncounter && 
			player->searchInventory("Classroom3Key") &&
			player->getRoom() == "Hallway" &&
			player->getPos().x <= 5.0f) {
			//Spawn monster
			cout << "Second chase" << endl;
			monster->setRoom("Hallway");
			monster->setPos(Vec3(20.0f, -3.0f, 0.0f));
			monster->setState(THunt);
			player->setProgress(GSecondChase);
		}
		//If first encounter, disable monster
		else if (player->getProgress() == GFirstEncounter) {
			monster->setState(TInactive);
		}
		else if (player->getProgress() == GStaffRoom) {
			monster->setState(TInactive);
		}

		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

void GameManager::SceneSwitch(string roomName_){
	//Destroy current scene
	currentScene->OnDestroy();
	delete currentScene;

	if (roomName_ == "dead") {
		currentScene = new ImageScene(windowPtr->GetSDL_Window());
		currentScene->OnCreate();
	}
	else {
		Room *room = map.searchRoom(roomName_);
		Vec3 newPlayerLoc = room->searchConnectedRooms(player->getPrevRoom())->getPos();
		player->setPos(newPlayerLoc);
		if (monster->getState() == TRoomSwitch) {
			monster->setPos(newPlayerLoc);
		}

		currentScene = new Scene0(windowPtr->GetSDL_Window(), room);
		currentScene->OnCreate();
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
	if (player) delete player;

}

