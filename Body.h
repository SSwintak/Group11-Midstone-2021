#ifndef BODY_H
#define BODY_H


#include "Vector.h"
#include "VMath.h"
#include "SDL_image.h"
#include <iostream>
#include <string>

using namespace std;

#define MAX_CHAR 20

using namespace MATH;

class Body {
	//friend class Player;
	friend class Physics;
	
protected:
	std::string name;
	Vec3 pos;
	Vec3 vel;
	Vec3 accel;
	float mass;
	SDL_Surface* image;
	SDL_Texture* texture;
	Vec3 imageSizeWorldCoords;

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
	void HandleEvents(const SDL_Event& sdlEvent);
	void setImage(SDL_Surface* image_) { image = image_; }
	SDL_Surface* getImage() { return image; }
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }

	void setImageSizeWorldCoords(Vec3 imageSizeWorldCoords_) {
		imageSizeWorldCoords.x = imageSizeWorldCoords_.x;
		imageSizeWorldCoords.y = imageSizeWorldCoords_.y;
		imageSizeWorldCoords.z = imageSizeWorldCoords_.z;
		imageSizeWorldCoords = imageSizeWorldCoords_;
	}
	Vec3 getImageSizeWorldCoords() { return imageSizeWorldCoords; }

};

#endif