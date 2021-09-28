#ifndef ROOM_H
#define ROOM_H

#include "GameObject.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Room{
private:
	string name;
	string imageName;
	vector<GameObject*> itemList;
	vector<string> connectedRooms; 
	//need to add rooms available for venting if the function is desired


public:
	Room(string name);
	~Room();
	void On_Create();
	void setName(string name_) { name = name_; }
	string getName() { return name; }
	string getimageName() { return imageName; }
	void setimageName(string imageName_) { imageName = imageName_; }
	void addItem(GameObject* item_);
	vector<GameObject*> getItemList() { return itemList; }
	GameObject* searchItem(string itemName_);
	void addConnectedRooms(GameObject connectedRooms_);

	//string searchConnectedRooms();

};

#endif
