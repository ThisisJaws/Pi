#include "SoundManager.h"

namespace SoundManager{
	namespace private_members{
		//Define all variables here to avoid multiple definition errors
		audiere::AudioDevicePtr device = audiere::OpenDevice();

		audiere::OutputStreamPtr mainMenu		= audiere::OpenSound(device, "Assets/Sound/ingame.wav");
		audiere::OutputStreamPtr buttonPress	= audiere::OpenSound(device, "Assets/Sound/ButtonPress.wav");
		audiere::OutputStreamPtr pickup			= audiere::OpenSound(device, "Assets/Sound/Pickup.mp3");
		audiere::OutputStreamPtr shoot			= audiere::OpenSound(device, "Assets/Sound/Shooting.wav");
	}

	//FUNCTION DEFINITIONS

	void playMusicMenu(bool repeat){
		private_members::mainMenu->play();
		private_members::mainMenu->setRepeat(repeat);
	}

	void playMusicLevel(LevelType level, bool repeat){
		//UNFISHED
	}

	void playSFXButtonPress(){
		private_members::buttonPress->play();
	}

	void playSFXPickup(){
		private_members::pickup->play();
	}

	void playSFXShoot(){
		private_members::shoot->play();
	}

	void stopAllSounds(){
		//UNFINISED
	}
}
