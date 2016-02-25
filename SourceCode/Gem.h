/* 
 * The gem collectable, just adds more score
 */

#ifndef GEM_H
#define	GEM_H

#include "Collectible.h"

class Gem : public Collectible{
    //VARIABLES
private:
    //how much to increase score by
    unsigned int scoreIncrease;
    
    //FUNCTIONS
public:
    //constructor
    Gem(irr::core::vector3df spawnPosition, const unsigned int &scoreIncrease, const irr::io::path &textPath, irr::scene::ISceneManager *sceneManagerReference, audiere::AudioDevicePtr audiereDevice);
 
    virtual void performAction(PlayerShip *player) override;
};

#endif	/* GEM_H */

