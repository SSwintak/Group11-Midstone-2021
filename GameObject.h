#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Body.h"



class GameObject : public Body {

private:
	string description;
	string imageName;

public:
	GameObject(std::string name_);
	~GameObject();
	string getDescription() { return description; }
	void setDescription(string description_) { description = description_; }
	string getimageName() { return imageName; }
	void setimageName(string imageName_) { imageName = imageName_; }
};

#endif

