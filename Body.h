#ifndef BODY_H
#define BODY_H


#include "Vector.h"
#include "VMath.h"
#include "SDL_image.h"
#include <iostream>
#include <string>
#include "ImageTexture.h"

using namespace std;
using namespace MATH;

#define MAX_CHAR 20



class Body: public ImageTexture {
	
	friend class Physics;
	
protected:
	std::string name;
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;

	bool collide;
	string currRoom;


	    //movement speed//    
	const float walksp = 5.5f;
	const float runsp = 8.0f;
	/*const float sneaksp = 3.0f;*/ //not needed but could be added so it's optional//

public:
	Body();
	Body(std::string name_, Vec3 pos_, Vec3 vel_, float mass_);
	~Body();
	void Update(float deltaTime);
	std::string getName() { return name; }
	void setName(std::string name_) { name = name_; }
	Vec3 getPos() { return pos; }
	void setPos(Vec3 pos_) { pos = pos_; }
	Vec3 getVel() { return vel; }
	void setVel(Vec3 vel_) { vel = vel_; }
	bool checkCollide() { return collide; }
	void setCollide(bool collide_) { collide = collide_; }
	string getRoom() { return currRoom; }
	void setRoom(bool currRoom_) { currRoom = currRoom_; }
	void HandleEvents(const SDL_Event& sdlEvent);

	enum TypeID
	{
		TGameObject = 0,
		TPlayer,
		TArtificialIntelligence,
		TFollowPlayer,

		NUM_ACTOR_TYPES
	};
	static const char* Typenames[NUM_ACTOR_TYPES];

	enum State //character states both for player or whatever else is a movable "game object"
	{
		SActive,
		SPaused,
		SDead
	};

	State getState() const { return State; }
	void setState(State state) { State = state; }

private:

	State State;

};

#endif