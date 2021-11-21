#include "Player.h"

Player::Player(Vec3 pos_, Vec3 vel_, float mass_):
Body("Player", pos_, vel_, mass_){

	isMoving = false;
	flip = SDL_FLIP_NONE;
}

Player::~Player()
{


}

void Player::HandleEvents(const SDL_Event& sdlEvent)
{
	
	
}

void Player::PlayerController(const SDL_Event& sdlEvent)
{


	//---Right Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
	{
		vel.x = walksp;
		setIsMoving(true);
		setFlip(SDL_FLIP_NONE);
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
	{
		vel.x = 0.0f;
		setIsMoving(false);
	}

	//---Left Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	{
		vel.x = -walksp;
		setIsMoving(true);
		setFlip(SDL_FLIP_HORIZONTAL);
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	{
		vel.x = 0.0f;
		setIsMoving(false);
	}

	//---Up Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	{
		vel.y = walksp;
		setIsMoving(true);
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	{
		vel.y = 0.0f;
		setIsMoving(false);
	}

	//---Down Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	{
		vel.y = -walksp;
		setIsMoving(true);
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	{
		vel.y = 0.0f;
		setIsMoving(false);
	}


}

void Player::Update(float deltaTime) {
	if (!collide) {
		pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
		vel += accel * deltaTime;
	}
	else {
		vel += accel * deltaTime;
		vel *= -1.0f;
		pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
		collide = false;
	}

}

void Player::addInventory(GameObject *item_) {
	inventory.push_back(item_);
}






