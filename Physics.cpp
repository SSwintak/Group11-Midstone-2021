#include "Physics.h"




void Physics::SimpleNewtonMotion(Body &object, const float deltaTime) {
	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}

bool Physics::CollisionDetect(Body &object1, Body &object2){
	
	//Object2 is always static
	//Get values in x-axis and y-axis
	float object1Width = abs((object1.getImageSizeWorldCoords().x / 2.0f)); 
	float object2Width = abs((object2.getImageSizeWorldCoords().x / 2.0f));
	float object1Height = abs((object1.getImageSizeWorldCoords().y / 2.0f));
	float object2Height = abs((object2.getImageSizeWorldCoords().y / 2.0f));
	float expectedDistanceWidth = object1Width + object2Width;
	float expectedDistanceHeight = object1Height + object2Height;
	float yDistance = abs(object1.pos.y - object2.pos.y);
	float xDistance = abs(object1.pos.x - object2.pos.x);

	if (yDistance <= expectedDistanceHeight && xDistance <= expectedDistanceWidth) {
			//cout << "D:" << yDistance << "ED: " << expectedDistanceHeight << endl;
			return true;
	}

	return false;
}

bool Physics::InteractionDetect(Player &player, Body &object){

	//Get values in x-axis and y-axis
	float playerWidth = abs((player.getImageSizeWorldCoords().x / 2.0f));
	float objectWidth = abs((object.getImageSizeWorldCoords().x));
	float playerHeight = abs((player.getImageSizeWorldCoords().y / 2.0f));
	float objectHeight = abs((object.getImageSizeWorldCoords().y));
	float expectedDistanceWidth = playerWidth + objectWidth;
	float expectedDistanceHeight = playerHeight + objectHeight;
	float yDistance = abs(player.pos.y - object.pos.y);
	float xDistance = abs(player.pos.x - object.pos.x);

	if (yDistance <= expectedDistanceHeight && xDistance <= expectedDistanceWidth) {
		//cout << "Can interact with " << object.getName() << endl;
		return true;

	}

	return false;

}

