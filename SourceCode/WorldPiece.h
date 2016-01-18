#ifndef WORLDPIECE_H
#define WORLDPIECE_H

#include "StaticObject.h"

class WorldPiece : public StaticObject{
	//VARIABLES

	//FUNCTIONS
public:
	//constructor
	WorldPiece(const irr::core::vector3df &spawnPosition, const irr::core::vector3df &spawnRotation, const irr::core::vector3df &spawnScale, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
};

#endif //WORLDPIECE_H