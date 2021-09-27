#ifndef PHYSICS_H
#define PHYSICS_H
#include "Body.h"

using namespace MATH;


class Physics{
public:
	static void SimpleNewtonMotion(Body& object, const float deltaTime);
	static bool CollisionDetect(Body& object1, Body& object2);
	static void CollisionResponse(Body& object1, Body& object2);

};

#endif
