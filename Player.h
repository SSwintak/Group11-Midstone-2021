#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"
#include "GameManager.h"
#include "GameObject.h"
#include <vector>


class Player : public Body {

private:
	vector<string> inventory;
	bool hint1;
	bool hint2;
	bool hint3;

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
};

#endif