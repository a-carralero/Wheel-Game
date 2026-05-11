#include "sys/input_tinyptc.hpp"
extern "C"{ 
#include "tinyPTC/src/tinyptc.h"
}


void InputSys_TinyPTC::keypress(KeySym k){
   keyboard.keyPressed(k);
}

void InputSys_TinyPTC::keyrelease(KeySym k){
   keyboard.keyRelease(k);
}

InputSys_TinyPTC::InputSys_TinyPTC(){
   ptc_set_on_keypress(keypress);
   ptc_set_on_keyrelease(keyrelease);
   keyboard.resetKeyboard();
}

bool InputSys_TinyPTC::isKeyPressed(KeySym k) const{
   return keyboard.isKeyPressed(k);
}

bool InputSys_TinyPTC::isKeyDown(KeySym k) const{
   return keyboard.isKeyPressed(k);
}

void InputSys_TinyPTC::preUpdate() const {
   ptc_process_events();
}
