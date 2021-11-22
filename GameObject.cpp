#include "GameObject.h"

GameObject::GameObject(std::string name_) {
	name = name_;
	detectionRange = 2.0f;
}

GameObject::~GameObject(){

}


void GameObject::displayDescription() {

	cout << description << endl;
}
