#pragma once
#include <cstdint>
#include "util/keysyms.hpp"

struct EntityManager;

struct InputSys_ImGui
{
   bool isKeyPressed(KeySym) const;
   bool isKeyDown(KeySym) const;
   void preUpdate() const {}
};
