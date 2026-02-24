#pragma once
#include <cstdint>
#include <array>
#include <numbers>
#include "cmp/component.hpp"
#include "util/vec2d.hpp"

struct PhysicsCmp: Component<PhysicsCmp>
{
   explicit PhysicsCmp(uint32_t eid)
      : Component(eid) {}
   
   static constexpr double kMaxV = 250.0;
   // drag = dt*vt*kdrag
   // En un segundo quiero que la velocidad se haga cero
   static constexpr double kDrag = 1.0;
   // Quiero que alcance la velocidad máxima en 0,5 seg 
   static constexpr double kMaxA = kMaxV / 0.5;
   // Una vuelta por segundo 
   static constexpr double kMaxVAng = (2.0*std::numbers::pi);

   Vec2D pos {}; 
   double orientation = 0.0;
   double v_linear = 0.0;
   double v_angular = 0.0;
   double acceleration = 0.0;
   double drag = kDrag;
};