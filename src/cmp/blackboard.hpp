#pragma once
#include "cmp/ai.hpp"

struct Blackboard
{
   Blackboard() = default;
   Blackboard(const Blackboard&) = delete;
   Blackboard(Blackboard&&) = delete;
   Blackboard& operator=(const Blackboard&) = delete;
   Blackboard& operator=(Blackboard&&) = delete;

   Vec2D target;
   SB behaviour = SB::Seek;
   bool tactive = false; 

   // Target Entity
   uint32_t teid = INVALID_EID;
};