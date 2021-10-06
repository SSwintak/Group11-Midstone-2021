#include "Player.h"

Player::Player(Vec3 pos_, Vec3 vel_, float mass_):
Body("Player", pos_, vel_, mass_)
{


}

Player::~Player()
{


}

void Player::HandleEvents(const SDL_Event& sdlEvent)
{
	
	
}

void Player::PlayerController(const SDL_Event& sdlEvent)
{
}
