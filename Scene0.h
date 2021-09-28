#ifndef SCENE0_H
#define SCENE0_H


#include "Scene.h"
#include "MMath.h"

using namespace MATH;

//Forward Declaration
union SDL_Event;
class Player;
class GameObject;
class FileLoader;

class Scene0 : public Scene {
private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer* renderer;
	Player *player;
	GameObject *flappybird;
	Matrix4 invProjectionMatrix;
	FileLoader *fileLoader;

	
public:
	Scene0(SDL_Window* sdlWindow);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
};

#endif

