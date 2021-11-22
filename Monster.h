#ifndef MONSTER_H
#define MONSTER_H

#include "Body.h"
#include <iostream>
#include <string>

class Monster{

public:
	string currRoom;
	bool huntState;
	bool normalState; // or wandering state

	Monster(string currRoom_);
	~Monster();
	void Update();
	void On_Destroy();
	string getCurrRoom() { return currRoom; }


};

#endif

