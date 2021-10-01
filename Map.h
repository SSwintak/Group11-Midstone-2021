#ifndef MAP_H
#define MAP_H

#include "Room.h"

/*
* This class is used as a database to store all the rooms.
* Each rooom should use "|" as a separator when storing
* First line is the name of the room
* Second line is the image name of the room (background image)
* Third line is the item list, use "," to separate the each item, no space
* Fourth line is the connected room list
* For example,
* Room1						<< name of the room
* RoomImage.png				<< image name of the room
* flappy,flappy2,			<< item list
* Room2,					<< connected room list
* |							<< separator between room
*
* (Remember to add "," at the end of the line so that program works)
*/


class Map {
public:
	static vector<Room*> roomList;

	static Room* searchRoom(string roomName_);
	static void loadRooms();
	static void On_Destroy();

};

#endif
