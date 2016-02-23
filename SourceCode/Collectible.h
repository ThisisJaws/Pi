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

	 //Text to animate when item is collected
	 irr::gui::IGUIStaticText *animatedText;

	 //Audoiere device and pick up sfx
	 audiere::OutputStreamPtr pickupSFX;
	 //Bool's to control the sound
	 bool soundStarted;
	 bool actionPefromed;

    //FUNCTIONS
public:
    //constructor
    Collectible(irr::core::vector3df spawnPosition, const irr::io::path &pathOfMesh, const irr::io::path &pathOfTexture, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice);
    
    //tick function will check for collision
    virtual void tick(irr::f32 deltaTime) override;
    
    //Gets called when the player collides with the colelctable
    void activate(PlayerShip *player);

	//Pure virtual function that performs the action the colecltible does, (i.e.e increase score)
	virtual void performAction(PlayerShip *player) = 0;

protected:
	//Displays the text on screen
	void displayText(const float &amount, const irr::core::stringw &text);
};

#endif	/* COLLLECTABLE_H */

