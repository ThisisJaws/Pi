#include "World.h"

#include "Game.h"

World::World(PlayerShip *player, float phase1WinPosition){
	this->player = player;
	this->phase1WinPosition = phase1WinPosition;

	phase1Loaded = false;
	phase2Loaded = false;
}

bool World::isPhase1Loaded(){
	return phase1Loaded;
}

bool World::isPhase2Loaded(){
	return phase2Loaded;
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
		return !Game::objectToUpdateContainsAnyType(TYPE_SHIP_ENEMY);
	} else{
		return false;
	}
}