#include "EventReceiver.h"

EventReceiver::EventReceiver(){
    //make sure all keys are false when this object gets created
    for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++){
        keyState[i] = Up;
    }

	joyStickEventHappened = false;
}

//called by the engine if an event has happened
bool EventReceiver::OnEvent(const irr::SEvent &event) {
	//If the event is a keyboard event
	if(event.EventType == irr::EET_KEY_INPUT_EVENT){
		//If the key is pressed down
		if(event.KeyInput.PressedDown){
			//If the key is not down
			if(keyState[event.KeyInput.Key] != Down){
				//Set it to Pressed
				keyState[event.KeyInput.Key] = Pressed;
			}else{
				//If it was Down, keep it Down
				keyState[event.KeyInput.Key] = Down;
			}
		}else{
			//If the key is no longer being pressed and is not Up
			if(keyState[event.KeyInput.Key] != Up){
				//Set to Released
				keyState[event.KeyInput.Key] = Released; 
			}
		}
	}
	
	//If the event is a joystick event
	if(event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && event.JoystickEvent.Joystick == 0){
		//Save the state for the return value
		joystickState = event.JoystickEvent;

		//Set the axis value
		xValue = (float)joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
		if(fabs(xValue) < DEAD_ZONE){
			xValue = 0;
			joyStickEventHappened = false;
		} else{
			joyStickEventHappened = true;
		}
		
		yValue = (float)joystickState.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
		if(fabs(yValue) < DEAD_ZONE){
			yValue = 0;
			joyStickEventHappened = false;
		} else{
			joyStickEventHappened = true;
		}

		//Set the stick direction
		if(xValue > 0){
			if(stickDirection[3] != Down){
				stickDirection[3] = Pressed;
			} else{
				stickDirection[3] = Down;
			}

			if(stickDirection[2] != Up){
				stickDirection[2] = Released;
			}
		} else if(xValue < 0){
			if(stickDirection[2] != Down){
				stickDirection[2] = Pressed;
			} else{
				stickDirection[2] = Down;
			}

			if(stickDirection[3] != Up){
				stickDirection[3] = Released;
			}
		} else{
			if(stickDirection[3] != Up){
				stickDirection[3] = Released;
			}

			if(stickDirection[2] != Up){
				stickDirection[2] = Released;
			}
		}
		if(yValue > 0){
			if(stickDirection[0] != Down){
				stickDirection[0] = Pressed;
			} else{
				stickDirection[0] = Down;
			}

			if(stickDirection[1] != Up){
				stickDirection[1] = Released;
			}
		} else if(yValue < 0){
			if(stickDirection[1] != Down){
				stickDirection[1] = Pressed;
			} else{
				stickDirection[1] = Down;
			}

			if(stickDirection[0] != Up){
				stickDirection[0] = Released;
			}
		} else{
			if(stickDirection[0] != Up){
				stickDirection[0] = Released;
			}

			if(stickDirection[1] != Up){
				stickDirection[1] = Released;
			}
		}

		//Check the state of each button
		for(int i = 0; i < 3; i++){
			if(joystickState.IsButtonPressed(i)){
				if(buttonKey[i] != Down){
					buttonKey[i] = Pressed;
				} else{
					buttonKey[i] = Down;
				}
			} else{
				if(buttonKey[i] != Up){
					buttonKey[i] = Released;
				}
			}
		}
	}
    
    return false;
}

void EventReceiver::endOfLoop(){
	//Loop through the key states
	for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++){
		//If the key was Released
		if(keyState[i] == Released){
			//Change it to up
			keyState[i] = Up;
		}
		//If the key was Pressed
		if(keyState[i] == Pressed){
			//Change it to Down
			keyState[i] = Down;
		}
	}

	//Do the same for the joy buttons
	for(int i = 0; i < 3; i++){
		if(buttonKey[i] == Released){
			buttonKey[i] = Up;
		}
		if(buttonKey[i] == Pressed){
			buttonKey[i] = Down;
		}
	}

	//And the stick directions
	for(int i = 0; i < 4; i++){
		if(stickDirection[i] == Released){
			stickDirection[i] = Up;
		}
		if(stickDirection[i] == Pressed){
			stickDirection[i] = Down;
		}
	}
}

bool EventReceiver::isKeyPressed(irr::EKEY_CODE keyCode){
	return keyState[keyCode] == Pressed;
}

bool EventReceiver::isKeyDown(irr::EKEY_CODE keyCode){
	return keyState[keyCode] == Down || keyState[keyCode] == Pressed;
}

bool EventReceiver::isKeyReleased(irr::EKEY_CODE keyCode){
	return keyState[keyCode] == Released;
}

irr::SEvent::SJoystickEvent EventReceiver::getJoyStickState(){
	return joystickState;
}

bool EventReceiver::isStartPressed(){
	return isKeyPressed(irr::KEY_RETURN) || buttonKey[BUTTON_A] == Pressed;
}

bool EventReceiver::isExitPressed(){
	return isKeyPressed(irr::KEY_ESCAPE) || buttonKey[BUTTON_B] == Pressed;
}

bool EventReceiver::isFirePressed(){
	return isKeyPressed(irr::KEY_KEY_J) || buttonKey[BUTTON_X] == Pressed;
}

bool EventReceiver::isUpPressed(){
	return isKeyPressed(irr::KEY_KEY_W) || stickDirection[0] == Pressed;
}

bool EventReceiver::isDownPressed(){
	return isKeyPressed(irr::KEY_KEY_S) || stickDirection[1] == Pressed;
}

bool EventReceiver::isLeftPressed(){
	return isKeyPressed(irr::KEY_KEY_A) || stickDirection[2] == Pressed;
}

bool EventReceiver::isRightPressed(){
	return isKeyPressed(irr::KEY_KEY_D) || stickDirection[3] == Pressed;
}

float EventReceiver::getHorizontalValue(){
	if(isKeyDown(irr::KEY_KEY_A)){
		return -1;
	} else if(isKeyDown(irr::KEY_KEY_D)){
		return 1;
	} else{
		if(joyStickEventHappened){
			return xValue;
		} else{
			return 0;
		}
	}
}

float EventReceiver::getVerticalValue(){
	if(isKeyDown(irr::KEY_KEY_W)){
		return 1;
	} else if(isKeyDown(irr::KEY_KEY_S)){
		return -1;
	} else{
		if(joyStickEventHappened){
			return yValue;
		} else{
			return 0;
		}
	}
}
