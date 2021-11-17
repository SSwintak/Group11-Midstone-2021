#include "Monster.h"
#include "Map.h"
#include "Room.h"
#include "Data.h"

//bool Monster::normalState;
//bool Monster::huntState;
//string Monster::currRoom;

Monster::Monster(string currRoom_){
	currRoom = currRoom_;
	huntState = false;
	normalState = true;
}

Monster::~Monster() {
	currRoom = "Room1";
	huntState = false;
	normalState = true;
}


/*
Check which state the monster is in to control the monster's action
Normal State: the monster wandering around the map
Hunt State: the monster follow the player to hunt him down

*/
void Monster::Update(){

	//if (normalState) {
	//	//Get currRoom's connnected room list
	//	Room *curr_Room = map.searchRoom(currRoom);
	//	vector<string> connectedRooms = curr_Room->getConnectedRooms();

	//	//Use random generator to decide on which room to go to
	//	int destRoomIndex = rand() % connectedRooms.size();
	//	int count = 0;
	//	//Find the room
	//	for (string roomName: connectedRooms) {
	//		if (count == destRoomIndex) {
	//			//Let the monster move to the destination room
	//			currRoom = roomName;
	//			break;
	//		}
	//	}
	//}
	//else if (huntState) {
	//	// do something
	//}

}

void Monster::On_Destroy(){

}
