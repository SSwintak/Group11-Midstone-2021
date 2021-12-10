#ifndef IMAGESCENE_H
#define IMAGESCENE_H


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

class ImageScene : public Scene{
	friend class TextureManager;

private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer *renderer;
	Matrix4 invProjectionMatrix;
	ImageTexture *imageDisplayed;
	Vec3 worldSizeScreenCoords;

	bool ImageTextureSetup(ImageTexture *target_);

public:
	ImageScene(SDL_Window* sdlWindow);
	~ImageScene();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	Room* getRoom();
};

#endif

