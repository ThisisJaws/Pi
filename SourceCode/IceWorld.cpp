#include "IceWorld.h"

#include "Game.h"

IceWorld::IceWorld(PlayerShip *player) 
	: World(player){

	//Load in all the file paths
	heightMapLocations[0] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece1.jpg";
	heightMapLocations[1] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece2.jpg";
	heightMapLocations[2] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece3.jpg";
	heightMapLocations[3] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece4.jpg";
	heightMapLocations[4] = "Assets/Environment/Levels/IceWorld/HeightMap-Piece5.jpg";

	//Load in the texture's file path
	terrainTexturePath = "Assets/Environment/Levels/IceWorld/IceWorldTexture.jpg";
}

void IceWorld::loadPhase1Obsticles(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void IceWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void IceWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}
