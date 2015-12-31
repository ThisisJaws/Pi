#include "IceWorld.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player){

}

void IceWorld::loadPhase1(irr::IrrlichtDevice * device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//load in the terrain
	terrain = loadTerrain(device,
						  "Assets/Environment/Levels/IceWorldHeightMap512x512.jpg",
						  driver->getTexture("Assets/Environment/Levels/IceWorldTexture.jpg"),
						  irr::core::vector3df(1, 1, 1));

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	phase1Loaded = true;
}

void IceWorld::loadPhase2(irr::IrrlichtDevice * device){
	if(terrain != NULL){
		terrain->remove();
	}

	//Make sure the previous phase is no longer considered loaded
	phase1Loaded = false;

	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Reset the player position
	player->changePosition(irr::core::vector3df(0, 0, 0));

	phase2Loaded = true;
}
