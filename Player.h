#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"
#include "Scene0.h"
#include "GameManager.h"
#include "GameObject.h"
#include <vector>


class Player : public Body {


private:
	vector<string> inventory;
	bool hint1;
	bool hint2;
	bool hint3;
	bool alive;

	bool isMoving;
	SDL_RendererFlip flip;
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
	void setAlive(bool alive_) { alive = alive_; }
	bool getAlive() { return alive; }
	void addInventory(GameObject *item_);
	bool getIsMoving() { return isMoving; }
	void setIsMoving(bool isMoving_) { isMoving = isMoving_; }
	SDL_RendererFlip getFlip() { return flip; }
	void setFlip(SDL_RendererFlip flip_) { flip = flip_; }
	vector<GameObject*> getInventory() { return inventory; }


};

#endif