/* 
 * Ammo collectable, gives the player more bullets
 */

#ifndef AMMO_H
#define	AMMO_H

#include "Collectable.h"

class Ammo : public Collectable{
    //VARIABLES
protected:
    //how much ammo to give
    int ammoIncrease;
    
    //FUNCTIONS
public:
    //constructor
    Ammo(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference);
    
    virtual void performAction(PlayerShip *player) override;
};

#endif	/* AMMO_H */

