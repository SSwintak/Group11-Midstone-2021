#ifndef ITEMPOOL_H
#define ITEMPOOL_H

/*
* This class is used as a database to store all the items.
* Each items should use "|" as a separator when storing
* First line is the name of the item
* Second line is the image name of the item
* Third line is the position of the item
* Fourth line is the velocity of the item
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
	
};


#endif
