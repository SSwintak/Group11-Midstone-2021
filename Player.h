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
	GSecondFloor,
	GEscape,
};


class Player : public Body {


private:
	vector<string> inventory;
	string prevRoom;
	bool hint1;
	bool hint2;
	bool hint3;
	bool hint4;
	bool hint5;
	bool alive;
	bool end;
	bool hasItem;
	GameProgress playerProgress;
	Matrix4 cameraHallway;
	Matrix4 cameraSecondFloor;
	
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
	void hint4Get() { hint4 = true; };
	void hint5Get() { hint5 = true; };
	int getHintNum();
	void setRoom(string roomName_) { currRoom = roomName_; }
	string getRoom() { return currRoom; }
	void setPrevRoom(string roomName_) { prevRoom = roomName_; }
	string getPrevRoom() { return prevRoom; }
	void switchRoom(string roomName_);
	void setAlive(bool alive_) { alive = alive_; }
	bool getAlive() { return alive; }
	void setEnd(bool end_) { end = end_; }
	bool getEnd() { return end; }
	void setProgress(GameProgress progress_) { playerProgress = progress_;	}
	GameProgress getProgress() { return playerProgress; }
	void setCameraHallway(Matrix4 camera_) { cameraHallway = camera_; }
	Matrix4 getCameraHallway() { return cameraHallway; }
	void setCameraSecondFloor(Matrix4 camera_) { cameraSecondFloor = camera_; }
	Matrix4 getCameraSecondFloor() { return cameraSecondFloor; }
	bool getHasItem() { return hasItem; }
	void reset();

};

#endif
