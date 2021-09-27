#ifndef BODY_H
#define BODY_H


#include "Vector.h"
#include "SDL_image.h"

using namespace MATH;


class Body {
	friend class Player;
	
private:
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	SDL_Surface* image;
	Vec3 imageSizeWorldCoords;

	    //movement speed//    
	const float walksp = 5.5f;
	const float runsp = 8.0f;
	/*const float sneaksp = 3.0f;*/ //not needed but could be added so it's optional//

public:
	Body();
	Body(Vec3 pos_, Vec3 vel_, float mass_);
	~Body();
	void Update(float deltaTime);
	Vec3 getPos() { return pos; }
	void setPos(Vec3 pos_) { pos = pos_; }
	Vec3 getVel() { return vel; }
	void setVel(Vec3 vel_) { vel = vel_; }
	void HandleEvents(const SDL_Event& sdlEvent);
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }

	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) {
		imageSizeWorldCoords.x = imageSizeWorldCoords_.x;
		imageSizeWorldCoords.y = imageSizeWorldCoords_.y;
		imageSizeWorldCoords.z = imageSizeWorldCoords_.z;
		imageSizeWorldCoords = imageSizeWorldCoords_;
	}
	Vec3 getImageSizeWorldCoords() { return imageSizeWorldCoords; }

};

#endif