#ifndef DOOR_H
#define DOOR_H

#include "Body.h"

class Door : public Body{

private:
	string connectedRoom;
	bool locked;

public:

	Door(string name_);
	~Door();
	string getConnectedRoom() { return connectedRoom; }
	void setLocked(bool locked_) { locked = locked_; }
	bool getLocked() { return locked; }
};

#endif
