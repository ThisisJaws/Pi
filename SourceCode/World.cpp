#include "World.h"

#include "Game.h"

World::World(PlayerShip *player){
	this->player = player;

	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;
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
			if(terrain != NULL){
				//Get an array to hold all of the edges
				irr::core::vector3d<irr::f32> edges[8];
				//Get the counding box of the mesh
				irr::core::aabbox3d<irr::f32> boundingBox = terrain->getTransformedBoundingBox();
				//Get the edges of the box
				boundingBox.getEdges(edges);

				if(player->getPosition().Z >= (edges[2].Z - edges[0].Z) / terrain->getScale().Z){
					phase1Complete = true;
					return true;
				} else{
					return false;
				}
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

void World::reset(){
	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;

	if(terrain){
		terrain->remove();
		terrain = 0;
	}
}

irr::scene::ITerrainSceneNode* World::loadTerrain(irr::IrrlichtDevice *device, const irr::io::path &heightMapFileLocation, irr::video::ITexture *texture, irr::core::vector3df &scaleFactor, float tileAmount){
	//Create the return variable
	irr::scene::ITerrainSceneNode *terrain = device->getSceneManager()->addTerrainSceneNode(heightMapFileLocation,					//Heightmap file
																							0,										//Parent Node
																							-1,										//Node ID
																							irr::core::vector3df(0),				//Position
																							irr::core::vector3df(0),				//Rotation
																							scaleFactor,							//Scale (Will have to get adjusted per map because some might be different lengths)
																							irr::video::SColor(255, 255, 255, 255),	//Colour
																							8,										//Max LOD (This depends on the patch size of the terrain which has to be 2^N+1)
																							irr::scene::ETPS_129,					//Patch size (What the LOD depends on)
																							1);										//Smoothfactor

	//Set the lighting
	terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	//Set the texture
	terrain->setMaterialTexture(0, texture);

	//Set the material type so it can be tiled
	terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);

	//Set how many times each texture is tiled
	terrain->scaleTexture(tileAmount, 1.0f);

	//Set the object ID for collision handling
	//terrain->setID(TYPE_STATIC_OBJECT);

	//Create the triangle selector for the terrain to handle collision
	irr::scene::ITriangleSelector *selector = device->getSceneManager()->createTerrainTriangleSelector(terrain);
	terrain->setTriangleSelector(selector);
	selector->drop();

	//Return the terrain
	return terrain;
}

