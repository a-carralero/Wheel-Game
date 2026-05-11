#include "sys/physics.hpp"
#include "man/entitymanager.hpp"
#include "cmp/physics.hpp"
#include <algorithm>
#include <cmath>
#include <numbers>

void PhysicsSys::update(EntityManager& g, double dt) const 
{
   constexpr double PI = std::numbers::pi;

   for(auto& phy: g.getCmpVector<PhysicsCmp>())
   {  
      phy.orientation += dt*phy.v_angular;
      if (phy.orientation > 2.0*PI) phy.orientation -= 2.0*PI;
      else if (phy.orientation < 0.0) phy.orientation += 2.0*PI;

      phy.v_linear += dt*phy.acceleration;
      phy.v_linear -= dt*phy.v_linear*phy.drag;
      phy.v_linear = std::clamp(phy.v_linear, 0.0, phy.v_max);
  
      phy.pos.x += dt*phy.v_linear*std::cos(phy.orientation);
      phy.pos.y += dt*phy.v_linear*std::sin(phy.orientation);
   }
}