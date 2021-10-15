#include "Physics.h"




void Physics::SimpleNewtonMotion(Body &object, const float deltaTime) {
	object.pos += object.vel * deltaTime + 0.5f * object.accel * deltaTime * deltaTime;
	object.vel += object.accel * deltaTime;
}

bool Physics::CollisionDetect(Body &object1, Body &object2, const float deltaTime){
	
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


	//Vec3 object1dir = Vec3(0.0f, 0.0f, 0.0f);
	//
	//if (VMath::mag(object1.vel) > VERY_SMALL) {
	//	object1dir = VMath::normalize(object1.vel);
	//}


	//If collide in x-axis or y-axis

	//if (object1dir.x < 0.0f || object1dir.x >= VERY_SMALL) {
	//	float expectedDistanceWidth = object1Width + object2Width;
	//	if (distance <= expectedDistanceWidth) {
	//		cout << "D:" << distance << " , ED: " << expectedDistanceWidth << endl;
	//		cout << "Collide on x" << endl;
	//		return true;
	//	}
	//}
	if (yDistance <= expectedDistanceHeight && xDistance <= expectedDistanceWidth) {
			cout << "D:" << yDistance << "ED: " << expectedDistanceHeight << endl;
			cout << "Collide" << endl;
			return true;
	}

	return false;
}

