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
	//----All variables will be initialised here----//
	namespace private_members{
		//Audiere device to handle the sounds
		audiere::AudioDevicePtr device = audiere::OpenDevice();

		//Main menu music
		audiere::OutputStreamPtr mainMenu = audiere::OpenSound(device, "Assets/Sound/ingame.wav");

		//Lava level music

		//Ice level music

		//Jungle level music

		//Button press SFX
		audiere::OutputStreamPtr buttonPress = audiere::OpenSound(device, "Assets/Sound/ButtonPress.wav");

		//Pickup SFX
		audiere::OutputStreamPtr pickup = audiere::OpenSound(device, "Assets/Sound/Pickup.mp3");

		//Shooting SFX
		audiere::OutputStreamPtr shoot = audiere::OpenSound(device, "Assets/Sound/Shooting.wav");
	}

	//Plays the menu music
	void playMusicMenu();

	//Plays the correct music for the level
	void playMusicLevel(LevelType level);

	//Plays the button SFX
	void playSFXButtonPress();

	//Plays the pickup SFX
	void playSFXPickup();

	//Plays the shooting SFX
	void playSFXShoot();

	//Stops all sounds
	void stopAllSounds();
}
#endif