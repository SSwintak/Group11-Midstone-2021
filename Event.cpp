#include "Event.h"
#include "Data.h"
#include "Map.h"



void Event::DoorSetup(string roomName_){
	if (roomName_ == "Custodian") {
		for (Door* door : map.searchRoom(roomName_)->getConnectedRooms()) {
			if (door->getName() == "Hallway") {
				door->setLocked(true);
			}
		}
	}
	else if (roomName_ == "Hallway") {
		for (Door* door : map.searchRoom(roomName_)->getConnectedRooms()) {
			if (door->getName() == "StaffRoom") {
				door->setLocked(true);
			}
		}
	}


}
