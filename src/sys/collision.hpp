#pragma once
#include <cstdint>
#include "cmp/collider.hpp"
#include "util/vec2d.hpp"

struct EntityManager;
struct PhysicsCmp;
struct Entity;

struct CollisionSys 
{
   void update(EntityManager& g) const;

 private:

   struct EntityData {
      Entity& e;
      PhysicsCmp& phy;
      ColliderCmp& col;

      EntityData(Entity& ent, PhysicsCmp& p, ColliderCmp& c)
         : e(ent), phy(p), col(c) {}
   };

   enum class CollisionKind{
      unknownKind ,
      playerGetsCollectable ,
      playerHitByBullet
   };
   
   void getCollectable(EntityManager& em, EntityData e1, EntityData e2) const;
   void hitByBullet(EntityManager& em, EntityData e1, EntityData e2) const;
   bool entitiesCollide(EntityData e1, EntityData e2) const;
   bool boxesCollide(Box<double>b1, Box<double>b2) const;
   CollisionKind collisionKind(const ColliderCmp& c1, const ColliderCmp& c2) const;
   Box<double> move2WorldFrame(const Box<double>& box, Vec2D pos) const;
   bool checkMasks(uint8_t type1, uint8_t against1, uint8_t type2, uint8_t against2) const;
   
};

