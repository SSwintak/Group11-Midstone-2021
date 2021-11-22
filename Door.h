#ifndef DOOR_H
#define DOOR_H

#include "Body.h"

class Door : public Body{

private:
	string connectedRoom;
	string requiredKey;

public:

	Door(string name_);
	~Door();
	string getConnectedRoom() { return connectedRoom; }


};

#endif
