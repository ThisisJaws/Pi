/* 
 * The gem collectable, just adds more score
 */

#ifndef GEM_H
#define	GEM_H

#include "Collectable.h"

class Gem : public Collectable{
    //VARIABLES
private:
    //how much to increase score by
    int scoreIncrease;
    
    //FUNCTIONS
public:
    //constructor
    Gem(irr::core::vector3df spawnPosition, irr::scene::ISceneManager *sceneManagerReference, irr::video::IVideoDriver *driverReference);
 
protected:
    virtual void activate() override;
};

#endif	/* GEM_H */

