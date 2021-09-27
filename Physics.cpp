#include "Physics.h"




void Physics::SimpleNewtonMotion(Body& object, const float deltaTime) {
	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}

bool Physics::CollisionDetect(Body& object1, Body& object2){
	
	//Find the absolute distance between the two objects
	float distance = VMath::distance(object1.getPos(), object2.getPos());
	
	//For x-axis
	float expectedDistanceWidth = (object1.getImageSizeWorldCoords().x / 2.0f) + (object2.getImageSizeWorldCoords().x / 2.0f);
	//For y-axis
	float expectedDistanceHeight = (object1.getImageSizeWorldCoords().y / 2.0f) + (object2.getImageSizeWorldCoords().y / 2.0f);
	//For diagonal movement
	float object1DistanceDiagonal = sqrt((object1.getImageSizeWorldCoords().x / 2.0f) * (object1.getImageSizeWorldCoords().x / 2.0f) +
										(object1.getImageSizeWorldCoords().y / 2.0f) * (object1.getImageSizeWorldCoords().y / 2.0f));
	float object2DistanceDiagonal = sqrt((object2.getImageSizeWorldCoords().x / 2.0f) * (object2.getImageSizeWorldCoords().x / 2.0f) +
		(object2.getImageSizeWorldCoords().y / 2.0f) * (object2.getImageSizeWorldCoords().y / 2.0f));
	float expectedDistanceDiagonal = object1DistanceDiagonal + object2DistanceDiagonal;

	//If collide in x-axis or y-axis
	if ((distance <= expectedDistanceWidth) || (distance <= expectedDistanceHeight))
		return true;
	//If collide in the corner
	else if ((distance <= expectedDistanceDiagonal))
		return true;

	return false;
}

