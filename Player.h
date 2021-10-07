#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"
#include "GameManager.h"





class Player : public Body
{
public:

	Player(Vec3 pos_, Vec3 vel_, float mass_);
	~Player();

	void HandleEvents(const SDL_Event& sdlEvent);
	void PlayerController(const SDL_Event& sdlEvent);
	
	

};

#endif