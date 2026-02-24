#include <numbers>
#include "sys/input.hpp"
#include "cmp/input.hpp"
#include "cmp/physics.hpp"
#include "man/entitymanager.hpp"
#include "cmp/blackboard.hpp"
extern "C"{ 
#include "tinyPTC/src/tinyptc.h"
}


void InputSys::keypress(KeySym k){
   keyboard.keyPressed(k);
}

void InputSys::keyrelease(KeySym k){
   keyboard.keyRelease(k);
}

InputSys::InputSys(){
   ptc_set_on_keypress(keypress);
   ptc_set_on_keyrelease(keyrelease);
   keyboard.resetKeyboard();
}

bool InputSys::isKeyPressed(KeySym k){
   return keyboard.isKeyPressed(k);
}


void InputSys::update(EntityManager& g) const
{
   // using namespace std::numbers;
   ptc_process_events();
   Blackboard& bb = g.getBlackboard();
   // static SB behaviour;

   for (auto& inp : g.getComponents<InputCmp>())
   {
      auto* phy = g.getRequiredCmpFromCmp<PhysicsCmp>(inp);
      if (!phy){
         std::cerr << "Error InputSys::update(), el component de input no tiene asociado un component de físicas\n";
         std::terminate();
      }
      phy->acceleration = 0; phy->v_angular = 0;
      
      if (keyboard.isKeyPressed(inp.left)) phy->v_angular = -phy->kMaxVAng/2.0;
      if (keyboard.isKeyPressed(inp.right)) phy->v_angular = phy->kMaxVAng/2.0;
      if (keyboard.isKeyPressed(inp.up)) phy->acceleration = phy->kMaxA;
      if (keyboard.isKeyPressed(inp.seek) && !bb.tactive){
         bb.target = phy->pos;
         bb.behaviour = SB::Seek;
         bb.tactive = true;
         bb.teid = inp.getEntityID();
         keyboard.keyRelease(inp.seek);
      }
      if (keyboard.isKeyPressed(inp.pursue) && !bb.tactive){
         bb.behaviour = SB::Pursue;
         bb.tactive = true;
         bb.teid = inp.getEntityID();
         keyboard.keyRelease(inp.pursue);
      }

      if (keyboard.isKeyPressed(inp.path_following) && !bb.tactive){
         bb.behaviour = SB::PathFollowing;
         bb.tactive = true;
         keyboard.keyRelease(inp.path_following);
      }



   }
}