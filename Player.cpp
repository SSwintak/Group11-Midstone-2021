#include "Player.h"
#include "Sounds.h"
#include <iostream>

Player::Player(Vec3 pos_, Vec3 vel_, float mass_) :
	Body("Player", pos_, vel_, mass_) {
	//hint1 = true;
	//hint2 = true;
	//hint3 = true;
	//hint4 = true;
	//hint5 = true;
	hint1 = false;
	hint2 = false;
	hint3 = false;
	hint4 = false;
	hint5 = false;
	alive = true;
	end = false;
	hasItem = false;
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

		if (Mix_Playing(CH_PLAYER) == 0) {
			playSound(SND_PLAYER_WALK, CH_PLAYER);
		}
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_D)
	{
		vel.x = 0.0f;
		setIsMoving(false);

		Mix_HaltChannel(CH_PLAYER);
	}

	//---Left Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	{
		vel.x = -walksp;
		setIsMoving(true);
		setFlip(SDL_FLIP_HORIZONTAL);

		if (Mix_Playing(CH_PLAYER) == 0) {
			playSound(SND_PLAYER_WALK, CH_PLAYER);
		}
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_A)
	{
		vel.x = 0.0f;
		setIsMoving(false);

		Mix_HaltChannel(CH_PLAYER);
	}

	//---Up Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	{
		vel.y = walksp;
		setIsMoving(true);

		if (Mix_Playing(CH_PLAYER) == 0) {
			playSound(SND_PLAYER_WALK, CH_PLAYER);
		}
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W)
	{
		vel.y = 0.0f;
		setIsMoving(false);

		Mix_HaltChannel(CH_PLAYER);
	}

	//---Down Movement---//
	if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	{
		vel.y = -walksp;
		setIsMoving(true);

		if (Mix_Playing(CH_PLAYER) == 0) {
			playSound(SND_PLAYER_WALK, CH_PLAYER);
		}
	}
	else if (sdlEvent.type == SDL_KEYUP && sdlEvent.key.keysym.scancode == SDL_SCANCODE_S)
	{
		vel.y = 0.0f;
		setIsMoving(false);

		Mix_HaltChannel(CH_PLAYER);
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
						cout << "hint5 added " << endl;
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
			hasItem = true;
			//acquire sticky note = acquire hint4
			if (item_->getName() == "Shoe") {
				hint2 = true;
				cout << "hint2 added" << endl;

			}
			if (item_->getName() == "PoliceDoc") {
				hint3 = true;
				cout << "hint3 added" << endl;

			}
			if (item_->getName() == "StickyNote") {
				hint4 = true;
				cout << "hint4 added" << endl;
				
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
	if (hint4) count++;
	if (hint5) count++;

	return count;
}

void Player::switchRoom(string roomName_){
	if (currRoom != roomName_) {
		prevRoom = currRoom;
		currRoom = roomName_;
	}
}

void Player::reset(){
	hint1 = false;
	hint2 = false;
	hint3 = false;
	hint4 = false;
	hint5 = false;
	alive = true;
	end = false;
	hasItem = false;
	prevRoom = "Custodian";
	setimageName("PlayerWalk_Sheet.png");
	setRoom("Custodian");
	playerProgress = GTheEntry;
	inventory = vector<string>();

}
