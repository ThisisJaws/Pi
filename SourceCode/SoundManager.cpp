#include "SoundManager.h"

void SoundManager::playMusicMenu(){
	private_members::mainMenu->play();
}

void SoundManager::playMusicLevel(LevelType level){
	//UNFISHED
}

void SoundManager::playSFXButtonPress(){
	private_members::buttonPress->play();
}

void SoundManager::playSFXPickup(){
	private_members::pickup->play();
}

void SoundManager::playSFXShoot(){
	private_members::shoot->play();
}

void SoundManager::stopAllSounds(){
	//UNFINISED
}
