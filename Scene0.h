#ifndef SCENE0_H
#define SCENE0_H


#include "Scene.h"
#include "MMath.h"
#include "TextureManager.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <vector>

using namespace MATH;
using namespace std;

//Forward Declaration
union SDL_Event;

class Scene0 : public Scene{
	friend class TextureManager;

private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer *renderer;
	Matrix4 invProjectionMatrix;
	class Room *room;
	SDL_Surface* roomImage;
	SDL_Texture* roomTexture;
	SDL_Surface* lightImage;
	SDL_Texture* lightTexture;
	SDL_Surface* darkImage;
	SDL_Texture* darkTexture;

	Vec3 worldSizeScreenCoords;
	SDL_Texture* texture;
	
public:
	Scene0(SDL_Window* sdlWindow, Room* roomName_);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	

	
};

#endif

