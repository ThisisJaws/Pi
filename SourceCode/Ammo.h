/* 
 * Ammo collectable, gives the player more bullets
 */

#ifndef AMMO_H
#define	AMMO_H

#include "Collectible.h"

class Ammo : public Collectible{
    //VARIABLES
protected:
    //how much ammo to give
    int ammoIncrease;
    
    //FUNCTIONS
public:
    //constructor
	Ammo(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::gui::IGUIEnvironment *guiEnvironment, audiere::AudioDevicePtr audiereDevice);
    
    virtual void performAction(PlayerShip *player) override;
};

#endif	/* AMMO_H */

