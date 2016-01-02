#include "JungleWorld.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player){

}

void JungleWorld::loadPhase1(irr::IrrlichtDevice * device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//load in the terrain
	terrain = loadTerrain(device,
						  "Assets/Environment/Levels/JungleWorldHeightMap512x512.jpg",
						  driver->getTexture("Assets/Environment/Levels/JungleWorldTexture.jpg"),
						  irr::core::vector3df(13, 1, 15));

	//Reset the player position
	player->changePosition(irr::core::vector3df(3500, 125, -500));

	phase1Loaded = true;
}

void JungleWorld::loadPhase2(irr::IrrlichtDevice * device){
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
