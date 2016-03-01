#include "IceWorld.h"

#include "Game.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player,  "Assets/LevelAssets/LevelMaps/IceWorld.stm", "Assets/SkyDomes/IceSkydome_small.jpg"){
}

void IceWorld::loadPhase2(irr::IrrlichtDevice * device, audiere::AudioDevicePtr audDevice){
}
