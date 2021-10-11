#include "Physics.h"




void Physics::SimpleNewtonMotion(Body &object, const float deltaTime) {
	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}

bool Physics::CollisionDetect(Body &object1, Body &object2, const float deltaTime){
	
	/*Change the method so it detects if the objects WILL COLLIDE */

	Vec3 pos1;
	Vec3 pos2;
	pos1 = object1.pos + (object1.vel * deltaTime + 0.5f * object1.accel * deltaTime * deltaTime);
	pos2 = object2.pos + (object2.vel * deltaTime + 0.5f * object2.accel * deltaTime * deltaTime);

	//Find the absolute distance between the two objects



	float distance = VMath::distance(pos1, pos2);
	
	//For x-axis
	float object1Width = abs((object1.getImageSizeWorldCoords().x / 2.0f)); 
	float object2Width = abs((object2.getImageSizeWorldCoords().x / 2.0f));

	Vec3 object1dir = Vec3(0.0f, 0.0f, 0.0f);
	
	if (VMath::mag(object1.vel) > VERY_SMALL) {
		object1dir = VMath::normalize(object1.vel);
	}


	//If collide in x-axis or y-axis

	if (object1dir.x <= 0.0f || object1dir.x >= VERY_SMALL) {
		float expectedDistanceWidth = object1Width + object2Width;
		if (distance <= expectedDistanceWidth) {
			return true;
		}
	}
	else if (object1dir.y <= 0.0f || object1dir.y >= VERY_SMALL) {
		float expectedDistanceHeight = abs((object1.getImageSizeWorldCoords().y)) + abs((object2.getImageSizeWorldCoords().y));
		if (distance <= expectedDistanceHeight) {
			return true;
		}
	}

	//If collide in the corner
	//else if ((distance <= expectedDistanceDiagonal))
	//	return true;

	return false;
}

