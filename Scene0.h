#ifndef SCENE0_H
#define SCENE0_H


#include "Scene.h"
#include "MMath.h"
#include "GameManager.h"
#include <iostream>
#include <string>
#include <vector>

using namespace MATH;
using namespace std;

//Forward Declaration
union SDL_Event;

class Scene0 : public Scene, public GameManager {
	friend class TextureManager;

private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer *renderer;
	Matrix4 invProjectionMatrix;
	class Room *room;
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

