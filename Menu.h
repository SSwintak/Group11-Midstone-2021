#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>


class Menu
{
private:

	bool isGameStart;
	bool mbLeftClicked;//mb = mouse button
	bool mbRightClicked;
	
	

public:


	Menu();
	~Menu();
	void HandleEvents(const SDL_Event& sdlEvent);
	void Update(float delaTime);
	bool getIsGameStart() { return isGameStart; }
	void setIsGameStart(bool isGameStart_) { isGameStart = isGameStart_; }
	bool getmbLeftClicked() { return mbLeftClicked; }
	void setmbLeftClicked(bool mbLeftClicked_) { mbLeftClicked = mbLeftClicked_; }




protected:

	

};

#endif