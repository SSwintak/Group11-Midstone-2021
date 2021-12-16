#include "Monster.h"
#include "Map.h"
#include "Room.h"
#include "Data.h"
#include "Player.h"

//bool Monster::normalState;
//bool Monster::huntState;
//string Monster::currRoom;

Monster::Monster(){
	currRoom = "Classroom3";
	monsterState = TNormal;
	setimageName("HorrorSchool_Monster_2_wandering_2.png");
	detectionRange = 2.0f;
	setPos(Vec3(5.0f, 10.0f, 0.0f));
	addSafeRoom("Classroom1");
}

Monster::~Monster() {
}


/*
Check which state the monster is in to control the monster's action
Normal State: the monster wandering around the map
Hunt State: the monster follow the player to hunt him down

*/
void Monster::Update(float deltaTime){

	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	vel += accel * deltaTime;

	if (monsterState == TWander) {
		setIsMoving(true);
		//Get currRoom's connnected room list
		Room *curr_Room = map.searchRoom(currRoom);
		vector<Door*> connectedRooms = curr_Room->getConnectedRooms();

		//Use random generator to decide on which room to go to
		int destRoomIndex = rand() % connectedRooms.size();
		int count = 0;
		//Find the room
		for (Door *room: connectedRooms) {
			if (count == destRoomIndex) {
				//Let the monster move to the destination room
				if (!isSafeRoom(room->getName())) {
					currRoom = room->getName();
					break;
				}
			}
			//delete roomName;
		}
		//delete curr_Room;
	}
	if (monsterState == THunt) {
		setIsMoving(true);
		// do something
		//vel.x = 2.0f;
		Vec3 playerDirection = VMath::normalize(player->getPos() - getPos());
		vel = playerDirection * 4.0f;
		if (vel.x <= 0.0f) { setFlip(SDL_FLIP_HORIZONTAL); }
		else if (vel.x >= 0.0f) { setFlip(SDL_FLIP_NONE); }
	}
	else {
		vel = Vec3(0.0f, 0.0f, 0.0f);
	}
}

void Monster::On_Destroy(){

}

void Monster::addSafeRoom(string safeRoom_){
	safeRooms.push_back(safeRoom_);
}

bool Monster::isSafeRoom(string room_){

	for (string room : safeRooms) {
		if (room_ == room) {
			return true;
		}
	}

	return false;
}

void Monster::switchRoom(string roomName_) {
	prevRoom = currRoom;
	currRoom = roomName_;
}

void Monster::reset(){
	monsterState = TNormal;
	setPos(Vec3(5.0f, 10.0f, 0.0f));
}

