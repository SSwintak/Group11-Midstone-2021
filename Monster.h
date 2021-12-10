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
	string prevRoom;


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
	void setPrevRoom(string roomName_) { prevRoom = roomName_; }
	string getPrevRoom() { return prevRoom; }
	void switchRoom(string roomName_);
	void reset();
};

#endif

