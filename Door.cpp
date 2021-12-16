#include "Door.h"

Door::Door(string name_){
	name = name_;
	setimageName("Door_1_720p.png");
	connectedRoom = name_;
	detectionRange = 0.6f;
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
