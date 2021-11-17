#ifndef SCENE_H
#define SCENE_H
#include <SDL.h>

class Scene {
private:
	class Room *room;

public:
	virtual Room* getRoom() = 0;
	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float time) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(const SDL_Event& sdlEvent) = 0;
};

#endif
