#include "World.h"

World::World(PlayerShip *player, float phase1WinPosition){
	this->player = player;
	this->phase1WinPosition = phase1WinPosition;

	phase1Loaded = false;
	phase2Loaded = false;
}

bool World::isPhase1Complete(){
	//Check if the player has complete phase 1
	if(phase1Loaded){
		return player->getPosition().Z >= phase1WinPosition;
	} else{
		return false;
	}
}

bool World::isPhase2Complete(){
	//Check if the player has completed phase 2
	if(phase2Loaded){
		for(std::list<Object*>::iterator shipIterator = shipReferences.begin(); shipIterator != shipReferences.end(); ++shipIterator){
			if(*shipIterator != NULL){
				//If any ship reference is still there the player hasnt completed the level
				return false;
			}
		}

		//if the loop completes then the level is complete
		return true;
	} else{
		return false;
	}
}