#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Body.h"

class GameObject : public Body {

public:
	GameObject(std::string name_, Vec3 pos_, Vec3 vel_, float mass_);


};

#endif

