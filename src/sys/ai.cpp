#include "sys/ai.hpp"
#include "man/entitymanager.hpp"
#include "cmp/ai.hpp"
#include "cmp/physics.hpp"
#include <algorithm>
#include <cmath>
#include <numbers>
#include "cmp/blackboard.hpp"
#include "util/controller.hpp"
#include "util/path.hpp"


void AiSys::update(EntityManager& g, double const dt) const 
{
   Blackboard& bb = g.getBlackboard();

   for(auto& ai: g.getComponents<AiCmp>())
   {  
      auto* phy_ptr = g.getRequiredCmpFromCmp<PhysicsCmp>(ai);
      if (!phy_ptr) return;

      auto& phy = *phy_ptr;
      phy.acceleration = phy.v_angular = 0.0;

      perception(bb, ai, dt);
      if (!ai.tactive) return;
      MotionCmd motion_cmd {};

      switch (ai.behaviour)
      {
         case SB::Arrive: 
            motion_cmd = arrive (ai.target, phy, ai.arrivalRadius, ai.time2arrive); 
            if (motion_cmd == MotionCmd{})
               ai.tactive = false;
            break;
         case SB::Seek:
            motion_cmd = seek(ai.target, phy, ai.time2arrive);
            break;
         case SB::Pursue: {
            Entity& e = g.getEntityByID(ai.teid);
            const PhysicsCmp* phyTarget = e.getComponent<PhysicsCmp>();
            if (!phyTarget){
               std::cerr << "The target entity has no physics component\n";
               std::terminate();
            }
            motion_cmd = pursue(*phyTarget, phy, ai.time2arrive);
            break;
         }
         case SB::PathFollowing:{
            static Path path (
               Vec2D{200,200}, 
               Vec2D{1400,200}, 
               Vec2D{1400,700}, 
               Vec2D{200,700}
            );
            motion_cmd = arrive(path.waypoint(), phy, ai.arrivalRadius, ai.time2arrive);
            if (motion_cmd == MotionCmd{})
               path.next();
         }
      }

      phy.acceleration = motion_cmd.acc;
      phy.v_angular = motion_cmd.v_angular;
   }
}

void AiSys::perception(Blackboard& bb, AiCmp& ai, const double dt) const
{
   ai.accumulated_dt += dt;
   if (ai.accumulated_dt <= ai.perceptionTime) return;
   // Perception time reached
   ai.accumulated_dt -= ai.perceptionTime;

   // Perception
   if (bb.tactive){
      if (bb.behaviour != ai.behaviour){
         ai.behaviour = bb.behaviour;
         ai.target = bb.target;
         bb.tactive = false;
         ai.tactive = true;
         ai.teid = bb.teid;
      }
      // std::printf("[%d] VOY! (%.1f,%.1f)\n", ai.getEntityID(), ai.tx, ai.ty);
   }
}


MotionCmd AiSys::arrive(Vec2D target, const PhysicsCmp& phy, double arrivalRadius, double time2arrive) const
{
   double dist = calcDistance(target, phy.pos);
   if (dist < arrivalRadius){
      std::cout << "He llegado!\n";
      return {};
   }
   double kp = 1.0/time2arrive;
   double velref = linearVelControl(target, phy.pos, kp*2.0, 0.0, phy.kMaxV);
   double acc = accelerationControl(velref, phy.v_linear, kp*2.0, -phy.kMaxA, phy.kMaxA);

   double theta_ref = calcAngleTarget(target, phy.pos);
   double ang_vel = orientationControl(theta_ref, phy.orientation, kp*6.0, -phy.kMaxVAng, phy.kMaxVAng);
   
   return {acc, ang_vel};
}

MotionCmd AiSys::seek(Vec2D target, const PhysicsCmp& phy, double time2arrive) const
{
   double kp = 1.0/time2arrive;
   double theta_ref = calcAngleTarget(target, phy.pos);
   double ang_vel = orientationControl(theta_ref, phy.orientation, kp*2.0, -phy.kMaxVAng, phy.kMaxVAng);
   // Pounding velocity
   double velref = phy.kMaxV / (1.0 + std::fabs(ang_vel)/3.0);
   std::cout << "seek velref = " << velref << "\n";
   std::cout << "state vel   = " << phy.v_linear << "\n";
   double acc = accelerationControl(velref, phy.v_linear, kp*6.0, -phy.kMaxA, phy.kMaxA);
   std::cout << "seek acc = " << acc << "\n";
   return {acc, ang_vel};
}

MotionCmd AiSys::pursue(const PhysicsCmp& phyTarget, const PhysicsCmp& phyPursuer, double time2arrive) const
{
   double dist = calcDistance(phyTarget.pos, phyPursuer.pos);
   double minimaltime = dist / phyPursuer.kMaxV;
   Vec2D target_vel {
      phyTarget.v_linear*std::cos(phyTarget.orientation),
      phyTarget.v_linear*std::sin(phyTarget.orientation)
   };
   Vec2D predicted_target = phyTarget.pos + target_vel*minimaltime;
   return seek (predicted_target, phyPursuer, time2arrive);
}