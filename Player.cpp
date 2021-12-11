#include "Player.h"

Player::Player(Vec3 pos_, Vec3 vel_, float mass_) :
	Body("Player", pos_, vel_, mass_) {
	hint1 = false;
	hint2 = false;
	hint3 = false;
	alive = true;
	end = false;
	prevRoom = "Custodian";
	setimageName("PlayerWalk_Sheet.png");
	setRoom("Custodian");
	playerProgress = GTheEntry;
}

Player::~Player(){
	hint1 = false;
	hint2 = false;
	hint3 = false;

}

void Player::HandleEvents(const SDL_Event& sdlEvent){


}

void Player::PlayerController(const SDL_Event& sdlEvent){


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
					if (item_->getName() == "FuseBox") {
						hint5 = true;
					}
					else {
						item_->displayDescription();
					}
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
			item_->displayDescription();
			cout << item_->getName() << " is added to the inventory" << endl;
			//acquire sticky note = acquire hint4
			if (item_->getName() == "LoseShoe") {
				hint2 = true;
			}
			if (item_->getName() == "PoliceDoc") {
				hint3 = true;
			}
			if (item_->getName() == "StickyNote") {
				hint4 = true;
				playerProgress = GSecondFloor;
			}
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
	//Set events for hints
	if (playerProgress == GTheEntry) {
		if (currRoom == "Hallway") {
			playerProgress = GTheSchool;
		}
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

int Player::getHintNum(){
	int count = 0;
	if (hint1) count++;
	if (hint2) count++;
	if (hint3) count++;

	return count;
}

void Player::switchRoom(string roomName_){
	if (currRoom != roomName_) {
		prevRoom = currRoom;
		currRoom = roomName_;
	}
}
