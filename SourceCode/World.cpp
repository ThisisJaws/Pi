#include "World.h"

#include "Game.h"

World::World(PlayerShip *player){
	this->player = player;

	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;
}

void World::loadPhase1(irr::IrrlichtDevice * device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Set the seed
	srand(1);
	//The position to place each terrain
	irr::core::vector3df terrainPos(0);
	//Loop through and place each terrain
	for(int i = 0; i < TERRAIN_NODE_COUNT; i++){
		//Random number for which tile to load
		int tile = rand() % HEIGHT_MAP_COUNT;
		//Create a terrain scene node using the tile selection
		terrainNodes[i] = loadTerrain(device, heightMapLocations[tile], driver->getTexture(terrainTexturePath), irr::core::vector3df(1), terrainPos);
		//Get an array to hold all of the edges
		irr::core::vector3d<irr::f32> edges[8];
		//Get the bounding box of the mesh
		irr::core::aabbox3d<irr::f32> boundingBox = terrainNodes[i]->getTransformedBoundingBox();
		//Get the edges of the box
		boundingBox.getEdges(edges);
		//Increase the starting pos by the length of the box
		terrainPos.Z += (edges[2].Z - edges[0].Z);
	}

	//Load in all the individual objects
	//loadPhase1Obsticlesgit(phase1StartPosition, smgr, driver);
	//loadPhase1Gems(phase1StartPosition, smgr, driver);
	//loadPhase1Ammo(phase1StartPosition, smgr, driver);

	//Set the player position to the phase start position
	player->changePosition(phase1StartPosition);

	//Phase is now loaded
	phase1Loaded = true;
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
		//Return if it is already complete to avoid uneccesary calculations
		if(phase1Complete){
			return true;
		} else{
			//Get an array to hold all of the edges
			irr::core::vector3d<irr::f32> edges[8];
			//Get the counding box of the mesh
			irr::core::aabbox3d<irr::f32> boundingBox = terrainNodes[TERRAIN_NODE_COUNT - 1]->getTransformedBoundingBox();
			//Get the edges of the box
			boundingBox.getEdges(edges);

			if(player->getPosition().Z >= edges[2].Z / terrainNodes[TERRAIN_NODE_COUNT - 1]->getScale().Z){
				phase1Complete = true;
				return true;
			} else{
				return false;
			}
		}
	} else{
		return false;
	}
}

bool World::isPhase2Complete(){
	//Check if the player has completed phase 2
	if(phase2Loaded){
		//Return if it is already complete to avoid uneccesary calculations
		if(phase2Complete){
			return true;
		} else{
			if(!Game::objectToUpdateContainsAnyType(TYPE_SHIP_ENEMY)){
				phase2Complete = true;
				return true;
			} else{
				return false;
			}
		}
	} else{
		return false;
	}
}

void World::clearTerrains(){
	for(int i = 0; i < TERRAIN_NODE_COUNT; i++){
		terrainNodes[i]->remove();
		terrainNodes[i] = 0;
	}
}

void World::reset(){
	//Remove any terrains
	if(phase1Loaded){
		clearTerrains();
	}

	//Reset the bools
	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;
}

irr::scene::ITerrainSceneNode* World::loadTerrain(irr::IrrlichtDevice *device, const irr::io::path &heightMapFileLocation, irr::video::ITexture *texture, irr::core::vector3df &scaleFactor, irr::core::vector3df position, irr::s32 smoothFactor, float tileAmount){
	//Create the return variable
	irr::scene::ITerrainSceneNode *terrain = device->getSceneManager()->addTerrainSceneNode(heightMapFileLocation,					//Heightmap file
																							0,										//Parent Node
																							-1,										//Node ID
																							irr::core::vector3df(0),				//Position - Changed below because of collision errors
																							irr::core::vector3df(0),				//Rotation
																							scaleFactor,							//Scale (Will have to get adjusted per map because some might be different lengths)
																							irr::video::SColor(255, 255, 255, 255),	//Colour
																							8,										//Max LOD (This depends on the patch size of the terrain which has to be 2^N+1)
																							irr::scene::ETPS_129,					//Patch size (What the LOD depends on)
																							smoothFactor);							//Smoothfactor

	//Set the lighting
	terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	//Set the texture
	terrain->setMaterialTexture(0, texture);

	//Set the material type so it can be tiled
	terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);

	//Set how many times each texture is tiled
	terrain->scaleTexture(tileAmount, 1.0f);

	//Set the position of the terrain
	terrain->setPosition(position);

	//Set the object ID for collision handling, 1 is reserved for terrain
	terrain->setID(1);

	//Create the triangle selector for the terrain to handle collision
	irr::scene::ITriangleSelector *selector = device->getSceneManager()->createTerrainTriangleSelector(terrain);
	terrain->setTriangleSelector(selector);
	selector->drop();

	//Return the terrain
	return terrain;
}

