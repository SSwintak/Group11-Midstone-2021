#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"

#include "Scene0.h"
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL.h>

#define FONT_SIZE    48

//Load font
static TTF_Font* font;
static SDL_Color white = { 255, 255, 255, 255 };
void initFonts(void);

extern SDL_Texture* getTextTexture(SDL_Renderer* renderer, const char* text);
extern SDL_Texture* toTexture(SDL_Renderer* renderer, SDL_Surface* surface, int destroySurface);

//Calculations
extern void blit(SDL_Renderer* renderer, SDL_Texture* texture, int x, int y, int center);

//Text Drawing
static SDL_Texture* helloWorld;
static int textAngle;

//Draw
void drawText(SDL_Renderer* renderer, const char* message, int posx, int posy, int center, int r, int g, int b);

