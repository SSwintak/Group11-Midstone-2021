#include "Player.h"

Player::Player(Vec3 pos_, Vec3 vel_, float mass_):
Body("Player", pos_, vel_, mass_){


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
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
	{
		vel.x = 0.0f;
	}

	//---Left Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	{
		vel.x = -walksp;
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	{
		vel.x = 0.0f;
	}

	//---Up Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	{
		vel.y = walksp;
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	{
		vel.y = 0.0f;
	}

	//---Down Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	{
		vel.y = -walksp;
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	{
		vel.y = 0.0f;
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






