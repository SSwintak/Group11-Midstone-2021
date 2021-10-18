#ifndef ROOM_H
#define ROOM_H

#include "GameObject.h"
#include <iostream>
#include <string>
#include <vector>
#include "SDL_image.h"

using namespace std;

class Room: public ImageTexture {
private:
	string name;
	int w;
	int h;
	vector<GameObject*> itemList;
	vector<string> connectedRooms;
	//need to add rooms available for venting if the function is desired


public:
	Room(string name);
	~Room();
	void setName(string name_) { name = name_; }
	string getName() { return name; }
	void setWidth(int w_) { w = w_; }
	int getWidth() { return w; }
	void setHeight(int h_) { h = h_; }
	int getHeight() { return h; }
	void addItem(GameObject* item_);
	vector<GameObject*> getItemList() { return itemList; }
	GameObject* searchItem(string itemName_);
	void addConnectedRooms(string connectedRooms_);
	vector<string> getConnectedRooms() { return connectedRooms; }


};

#endif
