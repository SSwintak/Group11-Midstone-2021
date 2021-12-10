#include "Sounds.h"
#include <fstream>
#include <iostream>
using namespace std;

Sounds::Sounds()
{
    LoadMedia();
}

Sounds::~Sounds()
{
    ClearSounds();
}

bool Sounds::LoadMedia()
{
    //Load music
    TestMusic = Mix_LoadMUS("audio/Loadingloop.wav");
    if (TestMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    //Load sound effects
    PlayerWalk = Mix_LoadWAV("audio/Wood_Walk01.mp3");
    if (PlayerWalk == NULL)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

	return success;
}

void Sounds::ClearSounds()
{
    //Free Sound and Music
    Mix_FreeMusic(TestMusic);
    TestMusic = NULL;
    Mix_FreeChunk(PlayerWalk);
    PlayerWalk = NULL;
}
