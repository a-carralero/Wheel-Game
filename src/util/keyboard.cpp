#include "util/keyboard.hpp"
#include <iostream>

bool* Keyboard::getMapElement(KeySym k){
   auto it = m_pressedKeys.find(k);
   if (it != m_pressedKeys.end()){
      return &it->second;
   } else{
      std::cerr << "getMapElement: la tecla no existe en el mapa\n";
      return nullptr;
   }
}

bool Keyboard::isKeyPressed(KeySym k)
{
   bool* keypressed = getMapElement(k);
   if (keypressed == nullptr)
      return false; // no existe la tecla
   else
      return *keypressed;
}

void Keyboard::keyPressed(KeySym k){
   auto* key = getMapElement(k);
   if (key != nullptr) *key = true;
}

void Keyboard::keyRelease(KeySym k){
   auto* key = getMapElement(k);
   if (key != nullptr) *key = false;
}

void Keyboard::resetKeyboard(){
   for (auto& elem: m_pressedKeys){
      elem.second = false;
   }
}