#ifndef DOOR_H
#define DOOR_H

#include "Body.h"

class Door : public Body{

private:
	string connectedRoom;
	string requiredKey;
	string description;
	bool locked;

public:

	Door(string name_);
	~Door();
	void setUp();
	string getConnectedRoom() { return connectedRoom; }
	void setLocked(bool locked_) { locked = locked_; }
	bool getLocked() { return locked; }
	void setRequiredKey(string requiredKey_) { requiredKey = requiredKey_; }
	string getRequiredKey(){ return requiredKey; }
	string getDescription() { return description; }
	void setDescription(string description_) { description = description_; }
	void displayDescription();
};

#endif
