#include <cmath>
#include <iostream>
#include <cassert>
#include <vector>
#include "sys/collision.hpp"
#include "man/entitymanager.hpp"
#include "cmp/physics.hpp"
#include "cmp/status.hpp"
#include "util/constants.hpp"

void CollisionSys::update(EntityManager& g) const 
{
   auto& collider_vec = g.getCmpVector<ColliderCmp>();
   std::vector<EntityData> entities;
   entities.reserve(collider_vec.size());

   // Cachear componente physics
   for (auto& c : collider_vec)
   {
      Entity& e = g.getEntityByID(c.getEntityID());
      auto& phy = e.getComponent<PhysicsCmp>();
      entities.emplace_back(e, phy, c);
   }

   std::size_t size = entities.size();

   for (std::size_t i=0; i<size; ++i)
   {
      auto& e1 = entities[i];

      for (std::size_t j=i+1; j<size; ++j)
      {
         auto& e2 = entities[j];

         if (checkMasks(
               e1.col.type_mask, e1.col.against_mask, 
               e2.col.type_mask, e2.col.against_mask) == 0) 
            continue;

         if (!entitiesCollide(e1, e2) ) continue;
         
         using CK= CollisionKind;
         switch (collisionKind(e1.col, e2.col))
         {
            case CK::playerGetsCollectable:{
               hitByBullet(g, e1, e2);
            } break;
            case CK::playerHitByBullet:{
               hitByBullet(g, e1, e2);
            } break;
            case CK::unknownKind: break;
         }
      }
   }
}


bool CollisionSys::
checkMasks(uint8_t type1, uint8_t against1, uint8_t type2, uint8_t against2) const
{
   return ((against1 & type2) && (against2 & type1) );
}

bool viceversaBitTest(uint8_t mask1, uint8_t typeA, uint8_t mask2, uint8_t typeB)
{
   return ((mask1 & typeA) && (mask2 & typeB)) || 
          ((mask1 & typeB) && (mask2 & typeA));
}


CollisionSys::CollisionKind 
CollisionSys::collisionKind(const ColliderCmp& c1, const ColliderCmp& c2) const
{
   using CK = CollisionKind;
   using CC = ColliderCmp;
   
   // Case 1: PLAYER vs COLLECTABLE
   if (viceversaBitTest(c1.type_mask, CC::CT_Player, c2.type_mask, CC::CT_Collectable))
      return CK::playerGetsCollectable;
   // Case 2: PLAYER vs BULLET
   else if (viceversaBitTest(c1.type_mask, CC::CT_Player, c2.type_mask, CC::CT_Bullet))
      return CK::playerHitByBullet;

   // Unknown collision Kind
   return CK::unknownKind;
}


Box<double> CollisionSys::
move2WorldFrame(const Box<double>& box, Vec2D pos) const
{
   return Box<double> {
      pos.x + box.xL,
      pos.x + box.xR,
      pos.y + box.yU,
      pos.y + box.yD
   };
}


bool CollisionSys::
boxesCollide(Box<double>b1, Box<double>b2) const
{
   auto checkIntervals = [](double L1, double R1, double L2, double R2)
   {
      if (L1 >= R2 || L2 >= R1)
         return false;
      else
          return true;
   };

   // check collision in both axes

   return checkIntervals(b1.xL, b1.xR, b2.xL, b2.xR) &&
          checkIntervals(b1.yU, b1.yD, b2.yU, b2.yD); 

}


bool CollisionSys::
entitiesCollide(EntityData e1, EntityData e2) const
{   
   // Entities can collide against each other, check if they collide
   // update location of boxes and check for collisions
   Box<double> box1 = move2WorldFrame(e1.col.AABB, e1.phy.pos);
   Box<double> box2 = move2WorldFrame(e2.col.AABB, e2.phy.pos);
   return boxesCollide(box1, box2);
}


void CollisionSys::
hitByBullet(EntityManager& em, EntityData e1, EntityData e2) const
{
   using CC = ColliderCmp;
   Entity* player = nullptr;
   Entity* bullet = nullptr;

   assert (viceversaBitTest(e1.col.type_mask, CC::CT_Player, e2.col.type_mask, CC::CT_Bullet));

   if (e1.col.isOfType(CC::CT_Player)){
      player = &e1.e;
      bullet = &e2.e;
   } else {
      player = &e2.e;
      bullet = &e1.e;
   }

   StatusCmp& pplayerstatus = player->getComponent<StatusCmp>();
   StatusCmp& pbulletstatus = bullet->getComponent<StatusCmp>();

   pplayerstatus.health -= pbulletstatus.health;

   // Destroy the bullet
   em.destroyEntityByID(bullet->getEntityID());
}


void CollisionSys::
getCollectable(EntityManager& em, EntityData e1, EntityData e2) const
{
   
   return;
}