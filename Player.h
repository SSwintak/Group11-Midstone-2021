#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"
#include "Scene0.h"
#include "GameManager.h"
#include "GameObject.h"
#include <vector>


class Player : public Body {


private:
	vector<GameObject*> inventory;
	bool hint1;
	bool hint2;
	bool hint3;
	bool isMoving;
	SDL_RendererFlip flip;
public:

	

	Player(Vec3 pos_, Vec3 vel_, float mass_);
	~Player();

	void HandleEvents(const SDL_Event& sdlEvent);
	void PlayerController(const SDL_Event& sdlEvent);
	void Update(float deltaTime);
	void addInventory(GameObject *item_);
	bool getIsMoving() { return isMoving; }
	void setIsMoving(bool isMoving_) { isMoving = isMoving_; }
	SDL_RendererFlip getFlip() { return flip; }
	void setFlip(SDL_RendererFlip flip_) { flip = flip_; }
	vector<GameObject*> getInventory() { return inventory; }


};

#endif