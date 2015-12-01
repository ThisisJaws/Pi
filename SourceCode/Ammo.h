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
protected:
    virtual void activate();
};

#endif	/* AMMO_H */
