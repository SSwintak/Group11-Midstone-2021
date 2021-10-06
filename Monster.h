#ifndef MONSTER_H
#define MONSTER_H

#include "Body.h"
#include <iostream>
#include <string>

class Monster{

public:
	static string currRoom;
	static bool huntState;
	static bool normalState; // or wandering state

	Monster(string currRoom_);
	~Monster();
	static void createMonster(string currRoom_);
	static void Update();
	static void On_Destroy();
	static string getCurrRoom() { return currRoom; }


};

#endif

