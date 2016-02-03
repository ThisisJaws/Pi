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
	enum LevelType{
		LAVA,
		ICE,
		JUNGLE
	};


	//Plays the menu music
	extern void playMusicMenu(const bool &repeat = true);

	//Plays the correct music for the level
	extern void playMusicLevel(const LevelType &level, const bool &repeat = true);

	//Plays the button SFX
	extern void playSFXButtonPress();

	//Plays the pickup SFX
	extern void playSFXPickup();

	//Plays the shooting SFX
	extern void playSFXShoot();

	//Stops all sounds
	extern void stopAllSounds();
}
#endif