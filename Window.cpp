#include "Window.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "Sounds.h"
#include <iostream> /// Umer likes this over printf() - too bad


Window::Window(int width_, int height_){
	screenSurface = nullptr;
	window = nullptr;
	width = width_;
	height = height_;
}

bool Window::OnCreate(){
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Initiate Text Fonts
	if (TTF_Init() < 0)
	{
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	//Open Audio Channels
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
		std::cout << "Couldn't initialize SDL Mixer" << std::endl;
	}
	Mix_AllocateChannels(MAX_SND_CHANNELS);

	window = SDL_CreateWindow("Horror Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == nullptr) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Window::OnDestroy(){
	/// Kill the surface first
	if (screenSurface) {
		SDL_FreeSurface(screenSurface);
	}

	/// Now kill the window
	if (window){
		SDL_DestroyWindow(window);
	}
	
	///Exit the SDL subsystems
	SDL_Quit();
	Mix_Quit();
	TTF_Quit();

}

Window::~Window(){}

SDL_Window* Window::GetSDL_Window() {
	return window;
}