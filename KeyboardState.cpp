#include "KeyboardState.h"

bool KeyboardState::GetKeyValue(SDL_Scancode keyCode) const
{
	if (keyCode) {
		return true;
	}
	if (!keyCode) {
		return false;
	}
}

ButtonState KeyboardState::GetKeyState(SDL_Scancode keyCode) const
{
	if (mPrevState[keyCode == 0])
	{
		if (mCurrentState[keyCode] == 0)
		{
			return ENone;
		}
		else
		{
			return EPressed;
		}
	}
	else //Previous state must be 1
	{
		if (mCurrentState[keyCode] == 0)
		{
			return EReleased;
		}
		else
		{
			return EHeld;
		}
	}
}


