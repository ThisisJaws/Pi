#include "EventReceiver.h"

EventReceiver::EventReceiver(){
    //make sure all keys are false when this object gets created
    for(irr::u32 i = 0; i < irr::KEY_KEY_CODES_COUNT; i++){
        keyIsDown[i] = false;
    }
}

//called by the engine if an event has happened
bool EventReceiver::OnEvent(const irr::SEvent &event) {
    //remember if each key is down or up
    if(event.EventType == irr::EET_KEY_INPUT_EVENT){
        keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    
    return false;
}

//return if that key is pressed or not
bool EventReceiver::isKeyDown(irr::EKEY_CODE keyCode) const{
    return keyIsDown[keyCode];
}