#pragma once
#include "cmp/status.hpp"
#include "man/entitymanager.hpp"

struct StatusSys
{
   void update(EntityManager& em, const double dt)
   {
      for (auto& st : em.getCmpVector<StatusCmp>())
      {
         // Update health
         st.health -= st.lostHealthPerSecond*dt;

         // Check for dying
         if (st.health <= 0.0){
            st.health = 0.0;
            em.destroyEntityByID(st.getEntityID());
         }

         // Update shooting time
         st.secondsSinceLastShot += dt;
      }
   }
};