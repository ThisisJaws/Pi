#include "WorldPiece.h"

WorldPiece::WorldPiece(const irr::core::vector3df &spawnPosition, const irr::core::vector3df &spawnRotation, const irr::core::vector3df &spawnScale, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference)
	: StaticObject(spawnPosition, pathOfMesh, pathOfTexture, sceneManagerReference, driverReference, false){

	//Rotate the piece
	changeRotation(spawnRotation);

	//Scale the piece
	getSceneNode()->setScale(spawnScale);
}
