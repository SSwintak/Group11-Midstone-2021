#include "Map.h"
#include <fstream>
#include "ItemPool.h"
#include "Data.h"


//vector<Room*> Map::roomList;

Map::Map()
{
}

Map::~Map()
{
}

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
		//Find room size
		string roomSize = roomStr.substr(0, roomStr.find("\n"));
		string roomW = roomStr.substr(0, roomStr.find(" "));
		room->setWidth(atoi(roomW.c_str()));
		roomSize.erase(0, roomW.length() + 1);
		roomStr.erase(0, roomW.length() + 1);
		string roomH = roomSize;
		room->setHeight(atoi(roomH.c_str()));
		roomStr.erase(0, roomSize.length() + 1);
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
				room->addItem(itemPool.searchItem(itemName));
		}
		roomStr.erase(0, 1);
		//Find connected room
		while (roomStr.at(0) != '\n') {
			string connectedRoom = roomStr.substr(0, roomStr.find("/"));
			roomStr.erase(0, connectedRoom.length() + 1);
			string connectedRoomName = connectedRoom.substr(0, connectedRoom.find("("));
			connectedRoom.erase(0, connectedRoomName.length() + 1);
			//Find Door position
			string DoorPosx = connectedRoom.substr(0, connectedRoom.find(","));
			connectedRoom.erase(0, DoorPosx.length() + 1);
			string DoorPosy = connectedRoom.substr(0, connectedRoom.find(","));
			connectedRoom.erase(0, DoorPosy.length() + 1);
			string DoorPosz = connectedRoom.substr(0, connectedRoom.find(")"));
			connectedRoom.erase(0, DoorPosz.length() + 1);
			//connectedRoom->setPos(Vec3(stof(posx), stof(posy), stof(posz)));
			//Add it to the connected room list
			Door* connectedDoor = new Door(connectedRoomName);
			connectedDoor->setPos(Vec3(stof(DoorPosx), stof(DoorPosy), stof(DoorPosz)));
			if (connectedRoom.empty())
				room->addConnectedRooms(connectedDoor);
		}
		//Add the room to the list
		roomList.push_back(room);
		content.erase(0, content.find("|") + 1);
		content.erase(0, content.find("\n") + 1);
	}
}

void Map::On_Destroy(){
	for (Room* obj : roomList) {
		//obj->On_Destroy();
		delete obj;
	}
}
