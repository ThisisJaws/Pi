#include "JungleWorld.h"

#include "Game.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player){

	//make the player start much higher
	phase1StartPosition = irr::core::vector3df(256, 200, -500);

	//Load in all the file paths
	heightMapLocations[0] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece1-512x512.jpg";
	heightMapLocations[1] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece2-512x512.jpg";
	heightMapLocations[2] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece3-512x512.jpg";
	heightMapLocations[3] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece4-512x512.jpg";
	heightMapLocations[4] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece5-512x512.jpg";

	//Load in the texture's file path
	terrainTexturePath = "Assets/Environment/Levels/JungleWorld/JungleWorldTexture.jpg";
}

void JungleWorld::loadPhase1Obsticles(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void JungleWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void JungleWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}
