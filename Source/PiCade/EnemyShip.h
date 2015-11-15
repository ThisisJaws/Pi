/* 
 * File:   EnemyShip.h
 * Author: pi
 *
 * Created on 15 November 2015, 13:16
 */

#ifndef ENEMYSHIP_H
#define	ENEMYSHIP_H

#include "Object.h"

class EnemyShip : public Object{
    //VARIABLES
    
    //FUNCTIONS
public:
    //override
    virtual void tick(irr::f32 deltaTime);
};

#endif	/* ENEMYSHIP_H */

