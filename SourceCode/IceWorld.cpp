#include "IceWorld.h"

#include "Game.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player){

	phase1StartPosition = irr::core::vector3df(5100, 170, -500);
}

void IceWorld::loadPhase1Obsticles(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void IceWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void IceWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}
