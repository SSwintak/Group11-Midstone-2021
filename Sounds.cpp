#include "Sounds.h"
#include <fstream>
#include <iostream>
using namespace std;

void initSounds(void)
{
	memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);
	//Start setting the pointers as Mix_Chunks

	music = NULL;

	loadSounds();
}

static void loadSounds(void)
{
	sounds[SND_PLAYER_WALK] = Mix_LoadWAV("audio/Walking.mp3");
	sounds[SND_PLAYER_OPEN] = Mix_LoadWAV("audio/DoorOpen06.mp3");
	sounds[SND_PLAYER_PICKUP] = Mix_LoadWAV("audio/ItemPickUp01.mp3");
	sounds[SND_MONSTER_GROWL] = Mix_LoadWAV("");
}

void loadMusic(const char* filename)
{
	if (music != NULL)
	{
		//Clear Previous Music
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = NULL;
	}

	music = Mix_LoadMUS(filename);
}

void playMusic(int loop)
{
	Mix_PlayMusic(music, (loop) ? -1 : 0);

		if (music == NULL)
	{
		printf("Failed to play music! SDL_mixer Error: %s\n", Mix_GetError());
	}
}

void playSound(int id, int channel)
{
	Mix_PlayChannel(channel, sounds[id], 0);

	if (sounds[id] == NULL)
	{
		printf("Failed to play sound! SDL_mixer Error: %s\n", Mix_GetError());
	}
}