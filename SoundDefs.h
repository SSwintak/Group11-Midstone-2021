#define MAX_SND_CHANNELS 8

enum
{
	//specify the channel through which a sound will play
	CH_ANY = -1,
	CH_PLAYER,
	CH_MONSTER
};

enum
{
	//identify a sound effect
	SND_PLAYER_WALK,
	SND_PLAYER_OPEN,
	SND_PLAYER_PICKUP,
	SND_MONSTER_GROWL,
	SND_MAX
};
