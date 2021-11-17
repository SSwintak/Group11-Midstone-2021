#include "Room.h"
#include <fstream>

Room::Room(string name_): name(name_){

}


Room::~Room(){}

void Room::On_Destroy(){
	for (GameObject* item : itemList) {
		delete item;
	}
	for (Door* door : connectedRooms) {
		delete door;
	}
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

void Room::addConnectedRooms(Door* connectedRooms_){
	connectedRooms.push_back(connectedRooms_);
}

void Room::removeItem(string itemName_){
	for (int i = 0; i < itemList.size(); i++) {
		if (itemList[i]->getName() == itemName_) {
			itemList.erase(itemList.begin() + i);
			break;
		}
	}

}


