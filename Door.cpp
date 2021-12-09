#include "Door.h"

Door::Door(string name_){
	name = name_;
	setimageName("DoorTest.png");
	connectedRoom = name_;
	detectionRange = 1.5f;
	locked = false;
}

Door::~Door(){
}
