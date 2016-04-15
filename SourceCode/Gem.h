/* 
 * The gem collectable, just adds more score
 */

#ifndef _GEM_H
#define	_GEM_H

#include "Collectible.h"

class Gem : public Collectible{
    //VARIABLES
private:
    //how much to increase score by
    unsigned int scoreIncrease;
    
    //FUNCTIONS
public:
    //constructor
    Gem(irr::core::vector3df spawnPosition, const unsigned int &scoreIncrease, const irr::io::path &textPath, irr::scene::ISceneManager *sceneManagerReference);
 
    virtual void performAction(PlayerShip *player) override;
};

#endif	/* _GEM_H */

