#ifndef ROOM_H
#define ROOM_H

#define MAX_ITEM 10

#include "GameObject.h"
#include <iostream>
#include <string>

using namespace std;

class Room{
private:
	string name;
	GameObject *itemList[MAX_ITEM];
	string connectedRooms[4]; //four entrances/exits at max
	//need to add rooms available for venting if the function is desired


public:
	Room(string name);
	~Room();
	void setName(string name_) { name = name_; }
	string getName() { return name; }
	void addItem(GameObject* item);
	//GameObject **getItemList() { return itemList; }
	//void setConnectedRooms(GameObject connectedRooms_) { connectedRooms = connectedRooms_; }
	string *getConnectedRooms() { return connectedRooms; }

};

#endif
