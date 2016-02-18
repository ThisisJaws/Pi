#include "SoundManager.h"

namespace SoundManager{
	//Variables the functions require
	audiere::AudioDevicePtr device = audiere::OpenDevice();

	//Music
	audiere::OutputStreamPtr mainMenu = audiere::OpenSound(device, "Assets/Sound/ingame.wav");
	//audiere::OutputStreamPtr scoreScreen = audiere::OpenSound(device, "Assets/Sound/ingame.wav");
	//audiere::OutputStreamPtr lavaLevel = audiere::OpenSound(device, "Assets/Sound/ingame.wav");
	//audiere::OutputStreamPtr iceLevel = audiere::OpenSound(device, "Assets/Sound/ingame.wav");
	//audiere::OutputStreamPtr jungleLevel = audiere::OpenSound(device, "Assets/Sound/ingame.wav");
	
	//SFX
	audiere::OutputStreamPtr buttonPress = audiere::OpenSound(device, "Assets/Sound/ButtonPress.mp3");
	audiere::OutputStreamPtr pickup = audiere::OpenSound(device, "Assets/Sound/Pickup.mp3");
	audiere::OutputStreamPtr shoot = audiere::OpenSound(device, "Assets/Sound/Shoot.mp3");
	
	//FUNCTION DEFINITIONS
	void playMusic(const MusicType &level, const bool &repeat){
		//Make sure all the other music is stopped
		mainMenu->stop();
		//scoreScreen->stop();
		//lavaLevel->stop();
		//iceLevel->stop();
		//jungleLevel->stop();

		//Switch to decide which music to play
		switch(level){
			case MENU:
				mainMenu->play();
				mainMenu->setRepeat(repeat);
				break;
				
			case SCORE:
				//scoreScreen->play();
				//scoreScreen->setRepeat(repeat);
				break;

			case LAVA:
				//None
				break;

			case ICE:
				//None
				break;

			case JUNGLE:
				//Nonw
				break;
		}
	}

	void playSFXButtonPress(){
		buttonPress->play();
	}

	void playSFXPickup(){
		pickup->reset();
		pickup->play();
	}

	void playSFXShoot(){
		shoot->reset();
		shoot->play();
	}
}
