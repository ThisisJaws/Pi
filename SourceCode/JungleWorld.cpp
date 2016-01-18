#include "JungleWorld.h"

#include "Game.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player, irr::core::vector3df(50, 200, -500)){
}