#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

/*
 * Sound manager namespace handles the playing of audio, it will have
 * sounds saved in it already as static members and all functions will be 
 * called statically
 */

#include "audiere.h"
#include <vector>

//Enum for level types
enum LevelType{
	LAVA,
	ICE,
	JUNGLE
};

// Using a namespace and declaring non-memeber functions is better than an 'all static' class
namespace SoundManager{
	namespace private_members{
		//Audiere device to handle the sounds
		extern audiere::AudioDevicePtr device;

		//Main menu music
		extern audiere::OutputStreamPtr mainMenu;

		//Lava level music

		//Ice level music

		//Jungle level music

		//Button press SFX
		extern audiere::OutputStreamPtr buttonPress;

		//Pickup SFX
		extern audiere::OutputStreamPtr pickup;

		//Shooting SFX
		extern audiere::OutputStreamPtr shoot;
	}

	//Plays the menu music
	extern void playMusicMenu(bool repeat = true);

	//Plays the correct music for the level
	extern void playMusicLevel(LevelType level, bool repeat = true);

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