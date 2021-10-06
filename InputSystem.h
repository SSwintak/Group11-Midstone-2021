#ifndef INPUTSYSTEM_H
#define INPUTSYSTEM_H
#include <SDL.h>
#include "Player.h"
#include "KeyboardState.h"

enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

struct InputState
{
	KeyboardState Keyboard;
	//Put current state of inputs here
};

class InputSystem
{
public:
	//Basically Oncreate and Ondestroy
	bool Initialize();
	void Shutdown();

	//This is called Before SDL_PollEvents
	void PrepUpdate();
	//This is called after SDL_PollEvents
	void Update();

	const InputState& GetState() const { return mState; } //Work In Progress

	InputState mState;
};
#endif

