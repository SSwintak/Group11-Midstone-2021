#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundDefs.h"

static Mix_Chunk* sounds[SND_MAX];
static Mix_Music* music;

extern void initSounds(void);
static void loadSounds(void);
extern void loadMusic(const char* filename);
extern void playMusic(int loop);
extern void playSound(int id, int channel);