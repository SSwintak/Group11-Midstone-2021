#include "InputSystem.h"

bool InputSystem::Initialize()
{
	//Assign the current state
	mState.Keyboard.mCurrentState = SDL_GetKeyboardState(NULL);
	//Clear previous state
	memset(mState.Keyboard.mPrevState, 0, SDL_NUM_SCANCODES);
	return true;
}

void InputSystem::Shutdown()
{
}

void InputSystem::PrepUpdate()
{
	//Coppy current data to the previous buffer
	//Current data is stale from the previous frame.
	//Only call this function when on a new frame but haven't called PollEvents.
	memcpy(mState.Keyboard.mPrevState, mState.Keyboard.mCurrentState, SDL_NUM_SCANCODES);
}

void InputSystem::Update()
{
}
