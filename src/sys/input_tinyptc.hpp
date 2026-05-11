#pragma once
#include <cstdint>
#include "util/keyboard.hpp"
#include "util/keysyms.hpp"

struct EntityManager;

struct InputSys_TinyPTC
{
 private:
   static inline Keyboard keyboard{};
 public:
   InputSys_TinyPTC();
   void preUpdate() const;
   bool isKeyPressed(KeySym) const;
   bool isKeyDown(KeySym) const;
   
   static void keypress(KeySym);
   static void keyrelease(KeySym);
};

