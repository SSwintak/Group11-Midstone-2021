#include "Body.h"


const char* Body::Typenames[NUM_ACTOR_TYPES] = {
	"GameObject",
	"Player",
	"ArtificialIntelligence",
	"FollowPlayer",

};

Body::Body(){

	State = SActive;

	pos.x = 0.0f;
	pos.y = 0.0f;
	pos.z = 0.0f;

	vel.x = 0.0f;
	vel.y = 0.0f;
	vel.z = 0.0f;

	accel.x = 0.0f;
	accel.y = 0.0f;
	accel.z = 0.0f;

	mass = 0.0f;

	image = nullptr;

}

Body::Body(std::string name_, Vec3 pos_, Vec3 vel_, float mass_):
	name(name_), pos(pos_), vel(vel_), mass(mass_), image(nullptr)
{

}

Body::~Body(){

}

void Body::Update(float deltaTime){

	pos += vel * deltaTime + 0.5f * accel * deltaTime * deltaTime;
	vel += accel * deltaTime;

}

void Body::HandleEvents(const SDL_Event& sdlEvent)
{
	
	
	
}
