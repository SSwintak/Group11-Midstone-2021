#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"
#include "GameManager.h"
#include "GameObject.h"
#include <vector>


class Player : public Body {

private:
	vector<GameObject*> inventory;
public:

	Player(Vec3 pos_, Vec3 vel_, float mass_);
	~Player();

	void HandleEvents(const SDL_Event& sdlEvent);
	void PlayerController(const SDL_Event& sdlEvent);
	void Update(float deltaTime);
	void addInventory(GameObject *item_);
	vector<GameObject*> getInventory() { return inventory; }

	

};

#endif