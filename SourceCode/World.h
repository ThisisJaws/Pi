#ifndef WORLD_H
#define WORLD_H

/* This class is the base class for each world (phase 1 & phase 2) */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

#include "irrlicht.h"

#include "EnemyTypes.h"
#include "PlayerShip.h"

#include "StaticObject.h"
#include "LavaPlume.h"

#include "CollectibleTypes.h"

class World{
	//VARIABLES
protected:
	//Reference to the player
	PlayerShip *player;

	//Keep track of which phase has been loaded
	bool phase1Loaded;
	bool phase2Loaded;

private:
	//String to the level data
	std::string levelLocation;

	//Vector of the all the terrain segments to tell when the player has beaten the level
	std::vector<StaticObject*> terrainSegments;

	//Location of the skydome file
	irr::io::path skyDomeLocation;

	//Keep track of what has been completed
	bool phase1Complete;
	bool phase2Complete;

	//Structured used for sorting vectors
	struct less_than_key{
		inline bool operator() (StaticObject *obj1, StaticObject *obj2){
			return (obj1->getPosition().Z < obj2->getPosition().Z);
		}
	};

	//FUNCTIONS
public:
	//constructor
	World(PlayerShip *player, const std::string &levelLocation, const irr::io::path &skyDomeLocation);

	//Functions to load the Stages for each level
	virtual void loadPhase1(irr::IrrlichtDevice *device);
	virtual void loadPhase2(irr::IrrlichtDevice *device) = 0;

	//Check if each phase is loaded
	bool isPhase1Loaded();
	bool isPhase2Loaded();

	//Check if the phase is complete
	bool isPhase1Complete();
	bool isPhase2Complete();

	//Loops through the array of terrain nodes and deletes them
	virtual void clearTerrains();

	//Returns the skydome location (file path) for the world
	irr::io::path getSkydomeLocation();

	//Resets the world
	void reset();

protected:
	//Loads in the map file for the level
	void loadMapFile(const std::string &mapFile, irr::IrrlichtDevice *device);
};

#endif /* WORLD_H */
