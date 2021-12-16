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
class ImageTexture;

class Scene0 : public Scene{
	friend class TextureManager;

private:
	SDL_Window *window;
	Matrix4 projectionMatrix;
	SDL_Renderer *renderer;
	Matrix4 invProjectionMatrix;
	class Room *room;
	class GameObject* itemName;
	ImageTexture *light;
	ImageTexture *deadScene;
	ImageTexture *playerHUD;
	//ImageTexture *items[8];// 0 = BKey
	int roomHeight;
	int roomWidth;
	Matrix4 projMa;
	Vec3 worldSizeScreenCoords;
	bool monsterExist;
	float timeCount;
	float timeDelay;
	bool camera;
	Vec3 projectionLoc;
	string message;

	bool ImageTextureSetup(ImageTexture *target_, bool animate);

public:
	Scene0(SDL_Window* sdlWindow, Room* roomName_);
	~Scene0();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render();
	void HandleEvents(const SDL_Event& sdlEvent);
	Room* getRoom() { return room; }


};

#endif
