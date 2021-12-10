#ifndef SCENE1_H
#define SCENE1_H


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
class ImageTexture;

class Scene1 : public Scene{
	friend class TextureManager;

private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer *renderer;
	Matrix4 invProjectionMatrix;
	Matrix4 projMa;
	Vec3 worldSizeScreenCoords;
	
	ImageTexture* mainMenu;
	ImageTexture* playButton;
	ImageTexture* quitButton;

	Menu* menu;
	

	bool ImageTextureSetup(ImageTexture *target_); 
	

public:
	Scene1(SDL_Window* sdlWindow);
	~Scene1();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	
	Room* getRoom()
	{
		return nullptr;
	}
	
};

#endif

