#include "World.h"

#include "Game.h"

World::World(PlayerShip *player){
	this->player = player;
	this->phase1WinPosition = phase1WinPosition;

	phase1Loaded = false;
	phase2Loaded = false;

	worldNode = 0;
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
		if(worldNode){
			//Get the extent of the Z axis
			irr::core::vector3df extent = worldNode->getTransformedBoundingBox().getExtent();
			return player->getPosition().Z >= (extent.Z + 100);
		} else{
			//TEMP - this else statement will no longer exists
			return player->getPosition().Z >= 4500.0f;
		}
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

void World::reset(){
	phase1Loaded = false;
	phase2Loaded = false;
}