#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"
#include "Scene0.h"
#include "GameManager.h"
#include "GameObject.h"
#include <vector>

enum GameProgress {
	GTheEntry = 0,
	GTheSchool,
	GFirstEncounter,
	GSecondChase,
	GStaffRoom,
};


class Player : public Body {

private:
	vector<string> inventory;
	string prevRoom;
	bool hint1;
	bool hint2;
	bool hint3;
	bool alive;
	bool win;
	GameProgress playerProgress;
	Matrix4 camera;
	
public:

	Player(Vec3 pos_, Vec3 vel_, float mass_);
	~Player();

	void HandleEvents(const SDL_Event& sdlEvent);
	void PlayerController(const SDL_Event& sdlEvent);
	bool interactObject(const SDL_Event& sdlEvent, GameObject* item_);
	void Update(float deltaTime);
	bool searchInventory(string item_);
	void addInventory(string item_);
	vector<string> getInventory() { return inventory; }
	void hint1Get() { hint1 = true; };
	void hint2Get() { hint2 = true; };
	void hint3Get() { hint3 = true; };
	void setRoom(string roomName_) { currRoom = roomName_; }
	string getRoom() { return currRoom; }
	void setPrevRoom(string roomName_) { prevRoom = roomName_; }
	string getPrevRoom() { return prevRoom; }
	void switchRoom(string roomName_);
	void setAlive(bool alive_) { alive = alive_; }
	bool getAlive() { return alive; }
	void setWin(bool win_) { win = win_; }
	bool getWin() { return win; }
	void setProgress(GameProgress progress_) { playerProgress = progress_;	}
	GameProgress getProgress() { return playerProgress; }
	void setCamera(Matrix4 camera_) { camera = camera_; }
	Matrix4 getCamera() { return camera; }
};

#endif