#pragma once
#include "cmp/component.hpp"
#include <cstdint>

struct StatusCmp: Component<StatusCmp>
{
   explicit StatusCmp(uint32_t eid)
      : Component(eid) {}
   
   double health = 0.0;
   double ammo = 0.0;

   double lostHealthPerSecond = 0.0; // para las balas, cuanto mas cerca mas daño, pasado un tiempo se autodestruyen
   double shotCoolDownSeconds = 0.5;
   double secondsSinceLastShot = 0.0; 
};