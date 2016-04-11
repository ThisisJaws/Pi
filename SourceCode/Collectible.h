/* 
 * The base class for all the collectables
 * all the individual properties for the collectables
 * will be in classes that inherit from this, this class
 * will just check for collisions
 */

#ifndef COLLLECTABLE_H
#define	COLLLECTABLE_H

#include "Object.h"
#include "PlayerShip.h"
#include "audiere.h"

class Collectible : public Object{
    //VARIABLES
 private:
     //variables to rate and move up and down
     float rotSpeed;

	 //Particle system scene node
	 irr::scene::IParticleSystemSceneNode *ps;

	 //Audoiere device and pick up sfx
	 //audiere::OutputStreamPtr pickupSFX;

	 //So it doesnt activate more than once
	 bool actionPefromed;

    //FUNCTIONS
public:
    //constructor
    Collectible(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice);

    //tick function will check for collision
    virtual void tick(irr::f32 deltaTime) override;
    
    //Gets called when the player collides with the colelctable
    void activate(PlayerShip *player);

	//Pure virtual function that performs the action the colecltible does, (i.e. increase score)
	virtual void performAction(PlayerShip *player) = 0;
};

#endif	/* COLLLECTABLE_H */

