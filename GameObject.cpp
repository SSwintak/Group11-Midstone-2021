#include "GameObject.h"

GameObject::GameObject(std::string name_) {
	name = name_;
}

GameObject::~GameObject(){

}


void GameObject::displayDescription() {

	cout << description << endl;
}
