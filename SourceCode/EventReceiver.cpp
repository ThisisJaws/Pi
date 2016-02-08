#include "EventReceiver.h"

EventReceiver::EventReceiver(){
    //make sure all keys are false when this object gets created
    for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++){
        keyState[i] = Up;
    }
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
}

bool EventReceiver::isKeyPressed(irr::EKEY_CODE keyCode){
	return keyState[keyCode] == Pressed;
}

//return if that key is pressed or not
bool EventReceiver::isKeyDown(irr::EKEY_CODE keyCode){
	return keyState[keyCode] == Down || keyState[keyCode] == Pressed;
}

bool EventReceiver::isKeyReleased(irr::EKEY_CODE keyCode){
	return keyState[keyCode] == Released;
}

irr::EKEY_CODE EventReceiver::getAnyKeyPressed(){
	//Loop through the key states
	for(int i = 0; i < irr::KEY_KEY_CODES_COUNT; i++){
		//Check if any key was pressed or down
		if(keyState[i] == Pressed || keyState[i] == Down){
			return (irr::EKEY_CODE)i;
		}
	}
}
