#include "Door.h"

Door::Door(string name_){
	name = name_;
	setimageName("DoorTest.png");
	connectedRoom = name_;

}

Door::~Door()
{
}
