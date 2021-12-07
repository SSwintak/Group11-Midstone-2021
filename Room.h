#ifndef ROOM_H
#define ROOM_H

#include "GameObject.h"
#include <iostream>
#include <string>
#include <vector>
#include "SDL_image.h"
#include "Door.h"

using namespace std;

class Room: public ImageTexture {
private:
	string name;
	int w;
	int h;
	vector<GameObject*> itemList;
	vector<Door*> connectedRooms;
	//need to add rooms available for venting if the function is desired


public:
	Room(string name);
	~Room();
	void On_Destroy();
	void setName(string name_) { name = name_; }
	string getName() { return name; }
	void setWidth(int w_) { w = w_; }
	int getWidth() { return w; }
	void setHeight(int h_) { h = h_; }
	int getHeight() { return h; }
	void addItem(GameObject* item_);
	vector<GameObject*> getItemList() { return itemList; }
	GameObject* searchItem(string itemName_);
	void removeItem(string itemName_);
	void addConnectedRooms(Door* connectedRooms_);
	vector<Door*> getConnectedRooms() { return connectedRooms; }
	Door* searchConnectedRooms(string roomName_);

};

#endif
