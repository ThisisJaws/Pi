/* 
 * Standard event receiver for getting user input
 */

#ifndef EVENTRECEIVER_H
#define	EVENTRECEIVER_H

#include "IEventReceiver.h"

//set up the class that inherits irrlicht's receiver class
class EventReceiver : public irr::IEventReceiver{
    //VARIABLES
private:
    //use this array to store the state of each key
    bool keyIsDown[irr::KEY_KEY_CODES_COUNT];
    
    //FUNCTIONS
public:
    //constructor
    EventReceiver();
    
    //override the pure virtual function to get the event
    virtual bool OnEvent(const irr::SEvent &event) ;
    
    //use this to check whether a key is being held down (const to make sure it is never overwritten))
    virtual bool isKeyDown(irr::EKEY_CODE keyCode) const;
};

#endif	/* EVENTRECEIVER_H */

