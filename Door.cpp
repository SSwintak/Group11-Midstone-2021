#include "Door.h"

Door::Door(string name_){
	name = name_;
	setimageName("DoorTest.png");
	connectedRoom = name_;
	detectionRange = 1.0f;
	locked = false;
	requiredKey = "";
	description = "";
}

Door::~Door(){
}

void Door::setUp(){

}

void Door::displayDescription(){
	cout << description << endl;
}
