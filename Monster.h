#ifndef MONSTER_H
#define MONSTER_H

#include "Body.h"
#include <iostream>
#include <string>
#include <vector>

enum MonsterState {
	TNormal = 0,
	TWander,
	THunt,
	TRoomSwitch,
	TInactive,

};


class Monster : public Body{

private:
	MonsterState monsterState;
	vector<string> safeRooms;


public:

	Monster();
	~Monster();
	void Update(float deltaTime);
	void On_Destroy();
	MonsterState getState() { return monsterState; }
	void setState(MonsterState state_) { monsterState = state_; }
	void addSafeRoom(string safeRoom_);
	bool isSafeRoom(string room_);
	vector<string> getSafeRooms() { return safeRooms; }


};

#endif
