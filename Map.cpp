#include "Map.h"
#include <fstream>
#include "ItemPool.h"


vector<Room*> Map::roomList;

Room* Map::searchRoom(string roomName_) {
	for (Room* obj : roomList) {
		if (obj->getName() == roomName_) {
			return obj;
		}
	}
    return nullptr;
}

void Map::loadRooms() {
	string pathName = "Database/Rooms.txt";
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
	file.close();

	//Loop through all the contents
	while (!content.empty()) {
		string roomStr = content.substr(0, content.find("|"));
		//Find room name
		string roomName = content.substr(0, content.find("\n"));
		Room* room = new Room(roomName);
		roomStr.erase(0, roomName.length() + 1);
		//Find room image name
		string roomImage = roomStr.substr(0, roomStr.find("\n"));
		room->setimageName(roomImage);
		roomStr.erase(0, roomImage.length() + 1);
		//Find item list
		while (roomStr.at(0) != '\n') {
			string itemName = roomStr.substr(0, roomStr.find(","));
			roomStr.erase(0, itemName.length() + 1);
			//Search the item from item pool and add it to the room
			if (!itemName.empty())
				room->addItem(ItemPool::searchItem(itemName));
		}
		//Find connected room
		while (roomStr.at(0) != '\n') {
			string connectedRoomName = roomStr.substr(0, roomStr.find(","));
			roomStr.erase(0, connectedRoomName.length() + 1);
			//Add it to the connected room list
			if (!connectedRoomName.empty())
				room->addConnectedRooms(connectedRoomName);
		}
		//Add the room to the list
		roomList.push_back(room);
		content.erase(0, content.find("|") + 1);
		content.erase(0, content.find("\n") + 1);
	}
}

void Map::On_Destroy(){
	for (Room* obj : roomList) {
		delete obj;
	}
}