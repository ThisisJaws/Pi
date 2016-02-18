#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

/*
 * Sound manager namespace handles the playing of audio, it will have
 * sounds saved in it already and they can be easily played by calling the function
 */

#include "audiere.h"
#include <vector>

// Using a namespace and declaring non-memeber functions is better than an 'all static' class
namespace SoundManager{
	//Enum for level types
	enum MusicType{
		MENU,
		SCORE,
		LAVA,
		ICE,
		JUNGLE
	};

	//Plays the correct music for the level
	extern void playMusic(const MusicType &level, const bool &repeat = true);

	//Plays the button SFX
	extern void playSFXButtonPress();

	//Plays the pickup SFX
	extern void playSFXPickup();

	//Plays the shooting SFX
	extern void playSFXShoot();
}
#endif