#include "IceWorld.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player, 10000){

}

void IceWorld::loadPhase1(irr::IrrlichtDevice * device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	//Load the mesh into the level
	worldNode = smgr->addAnimatedMeshSceneNode(smgr->getMesh("Assets/PlaceHolders/Levels/AllFourIceTerrainSeamless.obj"));
	worldNode->setPosition(irr::core::vector3df(0, -75, 10000));

	phase1Loaded = true;
}

void IceWorld::loadPhase2(irr::IrrlichtDevice * device){
	//Get the references
	irr::scene::ISceneManager *smgr = device->getSceneManager();
	irr::video::IVideoDriver *driver = device->getVideoDriver();

	phase2Loaded = true;
}
