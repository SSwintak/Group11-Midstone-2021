#include "Player.h"

Player::Player(Vec3 pos_, Vec3 vel_, float mass_):
Body("Player", pos_, vel_, mass_){
	hint1 = false;
	hint2 = false;
	hint3 = false;
	alive = true;
	setimageName("PlayerWalk_Sheet.png");
	setRoom("Custodian");
}

Player::~Player()
{
	hint1 = false;
	hint2 = false;
	hint3 = false;

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

bool Player::interactObject(const SDL_Event& sdlEvent, GameObject* item_) {
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) {

		//Check item type
		ObjectType itemType = item_->getType();

		if (itemType == TInteractable) {
			//If no required key, display description
			if (item_->getRequiredKey() == "") {
				item_->displayDescription();
				return true;
			}
			else {
				//Check inventory for required key
				if (searchInventory(item_->getRequiredKey())) {
					item_->displayDescription();
					return true;
				}
				else {
					cout << "Key required " << item_->getRequiredKey() << endl;
					return false;
				}
			}
		}
		else if (itemType == TPickable) {
			//add this to the player's inventory
			//remove this item from room
			addInventory(item_->getName());
			cout << item_->getName() << " is added to the inventory" << endl;
			return true;
		}
		//Static object cannot be interacted with
		else if (itemType == TStaticObject) {
			return false;
		}

	}

	return false;

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

bool Player::searchInventory(string item_)
{
	for (string itemName : inventory) {
		if (itemName == item_) {
			return true;
		}
	}
	return false;
}

void Player::addInventory(string item_) {
	inventory.push_back(item_);
}







