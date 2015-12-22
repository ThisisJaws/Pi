#include "World.h"

#include "Game.h"

World::World(PlayerShip *player){
	this->player = player;

	phase1Loaded = false;
	phase2Loaded = false;

	phase1Complete = false;
	phase2Complete = false;

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
		//Return if it is already complete to avoid uneccesary calculations
		if(phase1Complete){
			return true;
		} else{
			if(worldNode != NULL){
				//Get an array to hold all of the edges
				irr::core::vector3d<irr::f32> edges[8];
				//Get the counding box of the mesh
				irr::core::aabbox3d<irr::f32> boundingBox = worldNode->getTransformedBoundingBox();
				//Get the edges of the box
				boundingBox.getEdges(edges);

				if(player->getPosition().Z >= edges[2].Z - edges[0].Z){
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
}

irr::scene::ITerrainSceneNode* World::loadTerrain(irr::IrrlichtDevice *device, irr::io::IReadFile *heightMapFile, irr::video::ITexture *texture, float tileAmount = 20.0f){
	//Create the return variable
	irr::scene::ITerrainSceneNode *terrain = device->getSceneManager()->addTerrainSceneNode(heightMapFile);

	//Set the lighting
	terrain->setMaterialFlag(irr::video::EMF_LIGHTING, false);

	//Set the diffuse texture

	//Set the detail texture
	terrain->setMaterialTexture(1, texture);
	//Clear the pointer
	delete texture;

	//Set the material type so it can be tiled
	terrain->setMaterialType(irr::video::EMT_DETAIL_MAP);

	//Set how many times each texture is tiled
	terrain->scaleTexture(1.0f, tileAmount);
}

