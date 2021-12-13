#include "Text.h"
#include <iostream>

void initFonts(void)
{
	font = TTF_OpenFont("fonts/EnterCommand.ttf", FONT_SIZE);
	//Load font

	if (font == NULL) {
		std::cout << "initFont Error: " << SDL_GetError() << std::endl;
	}
}


SDL_Texture* getTextTexture(SDL_Renderer* renderer, const char* text)
{
	SDL_Surface* surface;

	surface = TTF_RenderUTF8_Blended(font, text, white);

	return toTexture(renderer, surface, 1);
}

SDL_Texture* toTexture(SDL_Renderer* renderer, SDL_Surface* surface, int destroySurface)
{
	SDL_Texture* texture;

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (destroySurface)
	{
		SDL_FreeSurface(surface);
	}

	if (texture == NULL) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
	}

	return texture;
}
//Text Calculations
void blit(SDL_Renderer* renderer, SDL_Texture *texture, int x, int y, int center)
{
	SDL_Rect dest;
	//Position
	dest.x = x;
	dest.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	if (center)
	{
		dest.x -= dest.w / 2;
		dest.y -= dest.h / 2;
	}

	SDL_RenderCopy(renderer, texture, NULL, &dest);
	if (!SDL_RenderCopy) {
		std::cout << "blit SDL_Error: " << SDL_GetError() << std::endl;
	}
	if (!SDL_QueryTexture) {
		std::cout << "QueryTexture SDL_Error: " << SDL_GetError() << std::endl;
	}
}

//Text Drawing
void drawText(SDL_Renderer* renderer, const char* message, int posx, int posy, int center, int r, int g, int b)
{
	helloWorld = getTextTexture(renderer, message);

	if (r > 0 || g > 0 || b > 0) {
		SDL_SetTextureColorMod(helloWorld, r, g, b);
	}

	blit(renderer, helloWorld, posx, posy, center);
}
