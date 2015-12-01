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
protected:
    virtual void activate();
};

#endif	/* GEM_H */

