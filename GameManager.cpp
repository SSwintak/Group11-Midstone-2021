#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Scene0.h"
#include "Scene1.h"
#include <iostream>
#include "ItemPool.h"
#include "Map.h"
#include "Monster.h"
#include "Data.h"

GameManager::GameManager() {
	windowPtr = nullptr;
	timer = nullptr;
	isRunning = true;
	gameStart = false;
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

	currentScene = new Scene1(windowPtr->GetSDL_Window());
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

				case SDL_SCANCODE_SPACE:

					if (!gameStart)
					{
						gameStart = true;
						//SceneSwitch("Custodian");
						currentScene->OnDestroy();
						if (currentScene) delete currentScene;
						player->setRoom("Custodian");
						currentScene = new Scene0(windowPtr->GetSDL_Window(), map.searchRoom("Custodian"));
						currentScene->OnCreate();

					}
					break;

				case SDL_SCANCODE_Q:
					cout << player->getProgress() << endl;
					cout << "Hint Num: " << player->getHintNum() << endl;
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

		if (gameStart) {
			//Player switch room
			if (!player->getEnd()) {
				if (player->getAlive()) {
					if (player->getRoom() == "Exit") {
						SceneSwitch("End");
						player->setEnd(true);
					}
					//Player switch room
					else if (player->getRoom() != currentScene->getRoom()->getName()) {
						//cout << "Room switching" << endl;
						SceneSwitch(player->getRoom());
					}
				}
				else if (!player->getAlive()) {
					SceneSwitch("dead");
					player->setEnd(true);
				}
			}

			//First encounter progress
			if (player->getProgress() == GTheSchool) {
				if (player->getRoom() == "Hallway" && 
					player->getPrevRoom() == "Classroom3" &&
					monster->getState() == TRoomSwitch) {
					player->hint1Get();
					player->setProgress(GFirstEncounter);
				}
			}
			//Monster Second Chase Part
			if (player->getProgress() == GFirstEncounter &&
				player->getRoom() == "Hallway" &&
				player->getPos().x <= 5.0f) {
				//Spawn monster
				cout << "Second chase" << endl;
				monster->setRoom("Hallway");
				monster->setPos(Vec3(13.0f, -3.0f, 0.0f));
				monster->setState(THunt);
				player->setProgress(GSecondChase);
			}
			//Disable monster when reaches ceratin progress
			else if (player->getProgress() == GFirstEncounter) {
				monster->setState(TInactive);
			}
			else if (player->getProgress() == GStaffRoom) {
				monster->setState(TInactive);
			}
			else if (player->getPrevRoom() == "Custodian" &&
				player->getHintNum() >= 5 &&
				player->getProgress() == GSecondFloor &&
				player->getPos().x <= 15.0f) {
				cout << "Last chase" << endl;
				monster->setRoom("SecondFloor");
				monster->setPos(Vec3(20.0f, -3.0f, 0.0f));
				monster->setState(THunt);
				player->setProgress(GEscape);
			}


			//Unlock doors in Hallway when player is at StaffRoom progress
			if (player->getProgress() == GStaffRoom) {
				Room* room = map.searchRoom("Hallway");
				room->searchConnectedRooms("Classroom2")->setLocked(false);
				room->searchConnectedRooms("Classroom3")->setLocked(false);
			}
			if (player->getProgress() == GFirstEncounter) {
				Room* room = map.searchRoom("Hallway");
				room->searchConnectedRooms("Classroom3")->setLocked(true);
			}

			//Hint related events
			if (player->getHintNum() >= 2) {
				Room* room = map.searchRoom("StaffRoom");
				room->searchConnectedRooms("BreakRoom")->setLocked(false);
			}
			if (player->getHintNum() >= 3) {
				Room* room = map.searchRoom("StaffRoom");
				room->searchConnectedRooms("MeetingRoom")->setLocked(false);
			}
			if (player->getHintNum() >= 4) {
				Room* room = map.searchRoom("Hallway");
				room->searchConnectedRooms("SecondFloor")->setLocked(false);
			}

		}
	
		/// Keep the event loop running at a proper rate
		SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec
	}
}

void GameManager::SceneSwitch(string roomName_){
	currentScene->OnDestroy();
	delete currentScene;

	if (roomName_ == "dead" || roomName_ == "End") {
		
		
		currentScene = new Scene1(windowPtr->GetSDL_Window());
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
