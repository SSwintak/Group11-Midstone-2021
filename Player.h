#ifndef PLAYER_H
#define PLAYER_H

#include "Body.h"


class Player : public Body
{
public:

	Player(Vec3 pos_, Vec3 vel_, float mass_);
	~Player();
	void setTexture(SDL_Texture* texture_) { texture = texture_; }
	SDL_Texture* getTexture() { return texture; }
	void HandleEvents(const SDL_Event& sdlEvent);


private:
	
	SDL_Texture* texture;

};

#endif