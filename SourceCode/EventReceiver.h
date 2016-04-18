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
	//Enumeration of keyboard events
	enum keyStates{
		Pressed,
		Down,
		Released,
		Up
	};

    //use this array to store the state of each key
	keyStates keyState[irr::KEY_KEY_CODES_COUNT];

	//Variable to hold the joystick state
	irr::SEvent::SJoystickEvent joystickState;

	//The three buttons we listen for on the joystick
	keyStates buttonKey[3]; //only check for 3 buttons 0: A 1: B 2: X

	enum buttons{
		BUTTON_A,
		BUTTON_B,
		BUTTON_X
	};
    
    //FUNCTIONS
public:
    //constructor
    EventReceiver();
    
    //override the pure virtual function to get the event
    virtual bool OnEvent(const irr::SEvent &event);

	//Place at the end of the game loop to update Keys
	void endOfLoop();
    
	//Returns true on the frame the key is pressed down
	virtual bool isKeyPressed(irr::EKEY_CODE keyCode);

    //Returns true while the key is pressed down
    virtual bool isKeyDown(irr::EKEY_CODE keyCode);

	//Returns true on the frame the key is released
	virtual bool isKeyReleased(irr::EKEY_CODE keyCode);

	//Returns the joystick state
	irr::SEvent::SJoystickEvent getJoyStickState();

	//Returns true on the frame the start button is pressed
	bool isStartPressed();

	//Returns true on the frame the exit button is pressed
	bool isExitPressed();

	//Returns true on the frame the fire button is pressed
	bool isFirePressed();
};

#endif	/* EVENTRECEIVER_H */

