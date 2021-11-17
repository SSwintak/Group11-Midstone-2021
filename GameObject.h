#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Body.h"

enum ObjectType
{
	TStaticObject,
	TInteractable,
	TPickable,

	NUM_ACTOR_TYPES
};



class GameObject : public Body {

private:
	string description;
	ObjectType type;
	string requiredKey; // or tool used to open this object

public:
	GameObject(string name_);
	~GameObject();
	string getDescription() { return description; }
	void setDescription(string description_) { description = description_; }
	ObjectType getType() { return type; }
	void setType(ObjectType type_) { type = type_; }
	string getRequiredKey() { return requiredKey; }
	void setRequiredKey(string requiredKey_) { requiredKey = requiredKey_; }
	void displayDescription();

};

#endif

