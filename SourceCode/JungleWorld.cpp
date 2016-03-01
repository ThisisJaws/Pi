#include "JungleWorld.h"

#include "Game.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player, "Assets/LevelAssets/LevelMaps/JungleWorld.stm", "Assets/SkyDomes/JungleSkydome_small.jpg"){
}

void JungleWorld::loadPhase2(irr::IrrlichtDevice * device, audiere::AudioDevicePtr audDevice){
}
