#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "ctype.h"

#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundDefs.h"

class Sounds {
public:
	//The music that will be played
	Mix_Music* TestMusic = NULL;

	//The sound effects that will be used
	Mix_Chunk* PlayerWalk = NULL;

	bool success = true;
	Sounds();
	~Sounds();
	bool LoadMedia();
	void ClearSounds();

};