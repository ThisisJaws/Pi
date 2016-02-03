#include "SoundManager.h"

namespace SoundManager{
	//Variables the functions require
	audiere::AudioDevicePtr device = audiere::OpenDevice();

	audiere::OutputStreamPtr mainMenu = audiere::OpenSound(device, "Assets/Sound/ingame.wav");
	audiere::OutputStreamPtr buttonPress = audiere::OpenSound(device, "Assets/Sound/ButtonPress.wav");
	audiere::OutputStreamPtr pickup = audiere::OpenSound(device, "Assets/Sound/Pickup.mp3");
	audiere::OutputStreamPtr shoot = audiere::OpenSound(device, "Assets/Sound/Shooting.wav");
	
	//FUNCTION DEFINITIONS

	void playMusicMenu(const bool &repeat){
		mainMenu->play();
		mainMenu->setRepeat(repeat);
	}

	void playMusicLevel(const LevelType &level, const bool &repeat){
		//UNFISHED
	}

	void playSFXButtonPress(){
		buttonPress->play();
	}

	void playSFXPickup(){
		pickup->play();
	}

	void playSFXShoot(){
		shoot->play();
	}

	void stopAllSounds(){
		//UNFINISED
	}
}
