#pragma once
#include <cstdint>
#include <vector>
#include "cmp/component.hpp"


template<typename T>
struct Box{
   T xL = 0, xR = 0;
   T yU = 0, yD = 0;
};

struct ColliderCmp: Component<ColliderCmp>
{
   explicit ColliderCmp(uint32_t eid)
      : Component(eid) {}
   
   enum ColliderType : uint8_t {
      CT_Player      = 0x01,   // 001
      CT_Collectable = 0x02,   // 010
      CT_Bullet      = 0x04,   // 100
   };

   Box<double> AABB;
   uint8_t type_mask = CT_Player;
   uint8_t against_mask = CT_Collectable | CT_Bullet;

   bool isOfType (ColliderType type) const { return type_mask & type; }
   bool collidesAgainst(ColliderType type) const {return against_mask & type; }
};