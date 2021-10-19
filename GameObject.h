#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Body.h"


class GameObject : public Body {

private:
	string description;
	string imageName;
	bool interactable;
	string requiredKey; // or tool used to open this object

public:
	GameObject(std::string name_);
	~GameObject();
	string getDescription() { return description; }
	void setDescription(string description_) { description = description_; }
	bool getInteractable() { return interactable; }
	void setInteractable(bool interactable_) { interactable = interactable_; }
	string getRequiredKey() { return requiredKey; }
	void setRequiredKey(string requiredKey_) { requiredKey = requiredKey_; }
	void displayDescription();

};

#endif

