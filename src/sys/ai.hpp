#pragma once
#include "util/vec2d.hpp"

struct EntityManager;
struct AiCmp;
struct PhysicsCmp;
struct Blackboard;

struct MotionCmd
{
   double acc = 0;
   double v_angular = 0;
   bool operator==(const MotionCmd&) const = default;
};

struct AiSys 
{
   void update(EntityManager& g, double const dt) const;
   void perception(Blackboard& bb, AiCmp& ai, double const dt) const;
   MotionCmd arrive(Vec2D target, const PhysicsCmp& phy, double arrivalRadius, double time2arrive) const;
   MotionCmd seek(Vec2D target, const PhysicsCmp& phy, double time2arrive) const;
   MotionCmd pursue(const PhysicsCmp& phyTarget, const PhysicsCmp& phyPursuer, double time2arrive) const;
};

