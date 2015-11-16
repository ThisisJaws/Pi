/* 
 * This is the class the enemies will use and will
 * controll all the AI that the enemies will need
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

