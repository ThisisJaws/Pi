#ifndef LAVAPLUME_H
#define LAVAPLUME_H

#include "StaticObject.h"

/*
 * The lava plumes are like most obsticles except they move up and down
 */

class LavaPlume : public StaticObject{
	//VARIABLES
private:
	//Max height to move up to
	float maxHeight;
	//Min Height to move down to
	float minHeight;

	//Speed to move
	float moveSpeed;
	float currentSpeed;

	//FUNCTIONS
public:
	LavaPlume(const irr::core::vector3df &spawnPosition, irr::scene::ISceneManager *sceneManagerReference);

	//Override to move up and down
	virtual void tick(irr::f32 deltaTime) override;
};

#endif