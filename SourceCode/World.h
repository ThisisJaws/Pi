#ifndef WORLD_H
#define WORLD_H

/* This class is the base class for each world (phase 1 & phase 2) */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "irrlicht.h"

#include "EnemyTypes.h"
#include "PlayerShip.h"

#include "WorldPiece.h"

#include "Windows.h"

#include "Ammo.h"
#include "Gem.h"

class World{
	//VARIABLES
protected:
	//Reference to the player
	PlayerShip *player;

private:
	//The light that will act as a sun
	irr::scene::ILightSceneNode *sun;

	//String to the level data
	std::string levelLocation;

	//Vector of the all the terrain segments to tell when the player has beaten the level
	std::vector<StaticObject *> terrainSegments;

	//Keep track of which phase has been loaded
	bool phase1Loaded;
	bool phase2Loaded;

	//Keep track of what has been completed
	bool phase1Complete;
	bool phase2Complete;

	//FUNCTIONS
public:
	//constructor
	World(PlayerShip *player, const std::string &levelLocation);

	/** abstract functions to load the levels
		Takes the device to load everything into the scene*/
	virtual void loadPhase1(irr::IrrlichtDevice *device);
	virtual void loadPhase2(irr::IrrlichtDevice *device);

	//Check if each phase is loaded
	bool isPhase1Loaded();
	bool isPhase2Loaded();

	//Check if the phase is complete
	bool isPhase1Complete();
	bool isPhase2Complete();

	//Loops through the array of terrain nodes and deletes them
	virtual void clearTerrains();

	//Resets the world
	void reset();

protected:
	//Loads in the map file for the level
	void loadMapFile(const std::string &mapFile, irr::IrrlichtDevice *device);
};

#endif /* WORLD_H */
