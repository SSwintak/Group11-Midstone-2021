#ifndef ITEMPOOL_H
#define ITEMPOOL_H

/*
* This class is used as a database to store all the items.
* Each items should use "|" as a separator when storing
* First line is the name of the item
* Second line is the image name of the item
* Third line is the position of the item, use "," to separate the axis, no space
* Fourth line is the velocity of the item
* Fifth line is the description of the item
* For example,
* flappy					<< name of the item
* TestPlayer.png			<< image name of the item
* 5.0,1.0,0.0				<< position
* 0.0,0.0,0.0				<< velocity
* Description				<< description
* |							<< separator between items
* 
*/

#include "GameObject.h"
#include <iostream>
#include <string>
#include <vector>

class ItemPool {
public:
    static vector<GameObject*> objectlist;

	static GameObject* searchItem(string itemName);
	static void loadItems();
	static void On_Destroy();
	
};


#endif