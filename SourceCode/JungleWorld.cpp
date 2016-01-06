#include "JungleWorld.h"

#include "Game.h"

JungleWorld::JungleWorld(PlayerShip *player)
	: World(player, irr::core::vector3df(0)){

	//Load in all the file paths
	heightMapLocations[0] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece1.jpg";
	heightMapLocations[1] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece2.jpg";
	heightMapLocations[2] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece3.jpg";
	heightMapLocations[3] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece4.jpg";
	heightMapLocations[4] = "Assets/Environment/Levels/JungleWorld/HeightMap-Piece5.jpg";

	//Load in the texture's file path
	terrainTexturePath = "Assets/Environment/Levels/JungleWorld/JungleWorldTexture.jpg";
}

void JungleWorld::loadPhase1Obsticles(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){
	//The pointer that will init all the islands into memory then be passed into the list
	StaticObject *floatingIsland;

	//Where the island will spawn
	irr::core::vector3df spawnPos = playerStartPos;

	//The path of the mesh and textures
	irr::io::path meshPath = "Assets/Environment/FloatingIslands/FloatingIsland1.obj";
	irr::io::path texturePath = "Assets/Environment/FloatingIslands/FloatIslandsTexture.jpg";

	//1
	//Get the spawn based off the player start position
	spawnPos.Z += 400;
	spawnPos.X += 0;
	spawnPos.Y += 30;
	//Create the new object
	floatingIsland = new StaticObject(spawnPos, meshPath, texturePath, sceneManager, videoDriver, false);
	//Put it on the update list
	Game::addObjectToUpdate(floatingIsland);
	//Reset the X and Y back to zero
	spawnPos.X = playerStartPos.X;
	spawnPos.Y = playerStartPos.Y;
}

void JungleWorld::loadPhase1Gems(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}

void JungleWorld::loadPhase1Ammo(const irr::core::vector3df & playerStartPos, irr::scene::ISceneManager * sceneManager, irr::video::IVideoDriver * videoDriver){

}
