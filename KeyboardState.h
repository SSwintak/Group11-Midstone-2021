#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H
#include <SDL.h>
#include "InputSystem.h"

class KeyboardState
{
public:
	friend class InputSystem; //Friend class so can be easily updated and accessed.

	bool GetKeyValue (SDL_Scancode keyCode) const; //Get bool value of key
	ButtonState GetKeyState(SDL_Scancode keyCode) const; //Get state based on current and previous frame

	//Current State
	const Uint8* mCurrentState;
	//Previous State
	Uint8 mPrevState[SDL_NUM_SCANCODES];
};

#endif
