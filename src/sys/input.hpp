#pragma once
#include <cstdint>
#include "man/entitymanager.hpp"
#include "cmp/blackboard.hpp"
#include "cmp/input.hpp"
#include "cmp/physics.hpp"
#include "cmp/status.hpp"
#include "util/keysyms.hpp"
#include "util/factory.hpp"
#include <cassert>


template <typename Backend>
struct InputSys 
{
 private:
   Backend backend;
   Factory& factory;

 public:
   InputSys(Factory& f) : factory(f) {} 

   bool isKeyPressed(KeySym k) const {
      return backend.isKeyPressed(k);
   }

   bool isKeyDown(KeySym k) const {
      return backend.isKeyDown(k);
   }

   bool isExitKeyPressed() const {
      return backend.isKeyPressed(KS_ESCAPE);
   }

   void update(EntityManager& g) const
   {
      backend.preUpdate();

      Blackboard& bb = g.getBlackboard();
      for (auto& inp : g.getCmpVector<InputCmp>())
      {
         Entity& e = g.getEntityByID(inp.getEntityID());
         auto& phy = e.getComponent<PhysicsCmp>();

         phy.acceleration = 0; phy.v_angular = 0;
         
         if (backend.isKeyDown(inp.left))  phy.v_angular = -phy.kMaxVAng/2.0;
         if (backend.isKeyDown(inp.right)) phy.v_angular = phy.kMaxVAng/2.0;
         if (backend.isKeyDown(inp.up)) phy.acceleration = phy.kMaxA;

         if (backend.isKeyPressed(inp.arrive) && !bb.tactive){
            bb.target = phy.pos;
            bb.behaviour = SB::Arrive;
            bb.tactive = true;
            bb.teid = inp.getEntityID();
         }
         if (backend.isKeyPressed(inp.seek) && !bb.tactive){
            bb.target = phy.pos;
            bb.behaviour = SB::Seek;
            bb.tactive = true;
            bb.teid = inp.getEntityID();
         }
         if (backend.isKeyPressed(inp.pursue) && !bb.tactive){
            bb.behaviour = SB::Pursue;
            bb.tactive = true;
            bb.teid = inp.getEntityID();
         }
         if (backend.isKeyPressed(inp.path_following) && !bb.tactive){
            bb.behaviour = SB::PathFollowing;
            bb.tactive = true;
         }
         if (backend.isKeyPressed(inp.space)){
            auto& st = e.getComponent<StatusCmp>();
            if(st.ammo > 0 && st.secondsSinceLastShot > st.shotCoolDownSeconds){
               --st.ammo;
               st.secondsSinceLastShot = 0.0;
               factory.createBullet(phy);
            }
         }
      }
   }



};