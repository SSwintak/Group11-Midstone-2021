#include "Room.h"
#include <fstream>

Room::Room(string name_): name(name_){

}


Room::~Room(){
}

void Room::On_Create(){
}

void Room::addItem(GameObject* item_){
	itemList.push_back(item_);
}

GameObject* Room::searchItem(string itemName_){
	for (GameObject* obj:itemList) {
		if (obj->getName() == itemName_) {
			return obj;
		}
	}
	return nullptr;
}

void Room::addConnectedRooms(GameObject connectedRooms_){
}


