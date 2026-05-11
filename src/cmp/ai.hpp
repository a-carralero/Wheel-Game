#pragma once
#include "util/vec2d.hpp"
#include "cmp/component.hpp"
#include <array>

enum class SB{
   Arrive = 0, 
   Seek,
   Pursue,
   PathFollowing
};

struct AiCmp : Component<AiCmp>
{
   Vec2D target;
   bool tactive = false;
   double arrivalRadius = 10.0;
   double time2arrive = 0.5;
   SB behaviour = SB::Arrive;

   // Perception time (cooldown)
   double perceptionTime = 0.5; // Frecuency inverse
   double accumulated_dt = 0.0;

   // Target Entity
   uint32_t teid = 0;

   static constexpr std::array SB_names {
      "Arrive", "Seek", "Pursue", "PathFollowing"
   };
};