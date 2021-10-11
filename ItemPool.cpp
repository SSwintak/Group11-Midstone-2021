#include "ItemPool.h"
#include <fstream>

//vector<GameObject*> ItemPool::objectlist;

GameObject* ItemPool::searchItem(string itemName) {
	for (GameObject *obj:objectlist) {
		if (obj->getName() == itemName) {
			return obj;
		}
	}
    return nullptr;
}

void ItemPool::loadItems() {

	string pathName = "Database/Items.txt";
	ifstream file(pathName);
	string line;
	string content;

	//If error
	if (!file) {
		std::cerr << "Can't open the file" << std::endl;
	}
	else {
		while (getline(file, line)) {
			content.append(line);
			content.append("\n");
		}
	}
	//Close file
	file.close();

	//Loop through all the contents
	while (!content.empty()) {
		string objectStr = content.substr(0, content.find("|"));
		//Find object name
		string objectName = content.substr(0, content.find("\n"));
		GameObject* object = new GameObject(objectName);
		objectStr.erase(0, objectName.length() + 1);
		//Find object image name
		string objectImage = objectStr.substr(0, objectStr.find("\n"));
		object->setimageName(objectImage);
		objectStr.erase(0, objectImage.length() + 1);
		//Find object position
		string posx = objectStr.substr(0, objectStr.find(","));
		objectStr.erase(0, posx.length() + 1);
		string posy = objectStr.substr(0, objectStr.find(","));
		objectStr.erase(0, posy.length() + 1);
		string posz = objectStr.substr(0, objectStr.find("\n"));
		objectStr.erase(0, posz.length() + 1);
		object->setPos(Vec3(stof(posx), stof(posy), stof(posz)));
		//Find object velocity
		string velx = objectStr.substr(0, objectStr.find(","));
		objectStr.erase(0, velx.length() + 1);
		string vely = objectStr.substr(0, objectStr.find(","));
		objectStr.erase(0, vely.length() + 1);
		string velz = objectStr.substr(0, objectStr.find("\n"));
		objectStr.erase(0, velz.length() + 1);
		object->setVel(Vec3(stof(velx), stof(vely), stof(velz)));
		//Find Description
		string description = objectStr.substr(0, objectStr.find("\n"));
		object->setDescription(description);
		//Add the object to the list
		objectlist.push_back(object);
		//Adjust the content string to loop next item
		content.erase(0, content.find("|") + 1);
		content.erase(0, content.find("\n") + 1);
	}
}

void ItemPool::On_Destroy() {
	for (GameObject* obj : objectlist) {
			delete obj;
	}

}

ItemPool::ItemPool()
{
}

ItemPool::~ItemPool()
{
}

