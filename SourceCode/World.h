#ifndef WORLD_H
#define WORLD_H

/* This class is the base class for each world (phase 1 & phase 2) */

#include <list>

#include "Irrlicht.h"

#include "EnemyTypes.h"
#include "PlayerShip.h"
#include "StaticObject.h"
#include "Ammo.h"
#include "Gem.h"

class World{
	//VARIABLES
protected:
	//Reference to the player
	PlayerShip *player;

	//Keep track of which phase has been loaded
	bool phase1Loaded;
	bool phase2Loaded;

	//Keep track of what has been completed
	bool phase1Complete;
	bool phase2Complete;

	//Scene nodes for the world
	irr::scene::ITerrainSceneNode *terrain;

	//FUNCTIONS
public:
	//constructor
	World(PlayerShip *player);

	/** abstract functions to load the levels
		Takes the device to load everything into the scene*/
	virtual void loadPhase1(irr::IrrlichtDevice *device) = 0;
	virtual void loadPhase2(irr::IrrlichtDevice *device) = 0;

	//Check if each phase is loaded
	bool isPhase1Loaded();
	bool isPhase2Loaded();

	//Check if the phase is complete
	bool isPhase1Complete();
	bool isPhase2Complete();

	//Resets the world
	virtual void reset();

protected:
	//Takes a height map and returns the loaded terrain
	irr::scene::ITerrainSceneNode* loadTerrain(irr::IrrlichtDevice *device, const irr::io::path &heightMapFileLocation, irr::video::ITexture *texture, irr::core::vector3df &scaleFactor = irr::core::vector3df(1, 1, 1), float tileAmount = 20.0f);
};

#endif /* WORLD_H */
