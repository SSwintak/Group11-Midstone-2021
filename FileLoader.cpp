#include "FileLoader.h"
#include <vector>

FileLoader::FileLoader(){

}


FileLoader::~FileLoader(){


}


void FileLoader::loadMap() {

}

Room* FileLoader::loadRoom(string name_) {
	//Declare a room
	Room *returnRoom = new Room(name_);
	
	string pathName = "Database/Room/";
	pathName.append(name_);
	pathName.append(".txt");

	ifstream file(pathName);
	string line;

	//If error
	if (!file) {
		std::cerr << "Can't open the file" << std::endl;
	}
	else {
		while (getline(file, line)) {
			//store it as a item in the list if the first char is 1
			if (line.at(0) == '1') {
				//do something
				cout << line.substr(1);
			//store it as a connected room in the list if the first char is 2
			}
			else if (line.at(0) == '2') {
				//do something

			}
		}
	}
	file.close();

	return returnRoom;
}

GameObject* FileLoader::loadGameObject(string name_) {
	//Declare a room
	GameObject* returnObject = new GameObject(name_);

	string pathName = "Database/Items/";
	pathName.append(name_);
	pathName.append(".txt");

	ifstream file(pathName);
	string line;

	//If error
	if (!file) {
		std::cerr << "Can't open the file" << std::endl;
	}
	else {
		while (getline(file, line)) {
			//store content as position if the first char is p
			if (line.at(0) == 'p') {
				//Manipulate strings to get the float numbers
				string posx = line.substr(1, line.find(',') - 1);
				string posy = line.substr(line.find(posx), line.find(',') - 1);
				returnObject->setPos(Vec3(stof(posx), stof(posy), 0.0f));
				//cout << "posx" << posx << endl;
				//cout << "posy" << posy << endl;
			}
			//store content as description if the first char is d
			else if (line.at(0) == 'd') {
				returnObject->setDescription(line.substr(1));
				//cout << returnObject->getDescription();
			}
			//store content as image name if the first char is d
			else if (line.at(0) == 'i') {
				
			}
		}
	}
	file.close();

	return returnObject;

}





