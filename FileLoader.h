#ifndef FILELOADER_H
#define FILELOADER_H

#include<iostream>
#include<fstream>
#include<string>
#include "Room.h"
#include "GameObject.h"

using namespace std;

class FileLoader {

private:
	//string path;

public:
	FileLoader();
	~FileLoader();

	Room* loadRoom(string name_);
	void loadMap();
	GameObject* loadGameObject(string name_);

};

#endif
