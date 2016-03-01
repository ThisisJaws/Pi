#include "LavaWorld.h"

#include "Game.h"

LavaWorld::LavaWorld(PlayerShip *player) 
	: World(player, "Assets/LevelAssets/LevelMaps/LavaWorld.stm", "Assets/SkyDomes/LavaSkydome_small.jpg"){
}

void LavaWorld::loadPhase2(irr::IrrlichtDevice * device, audiere::AudioDevicePtr audDevice){
}
