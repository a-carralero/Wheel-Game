#include "sys/spawn.hpp"
#include "man/entitymanager.hpp"
#include "cmp/spawner.hpp"
#include "cmp/physics.hpp"
#include "cmp/render.hpp"
#include "cmp/collider.hpp"
#include <cassert>
#include <iostream>


uint32_t SpawnSys::
SpawnNewEntity(SpawnType type, Vec2D pos)
{
   uint32_t eid = INVALID_EID;
   switch (type)
   {
      case SpawnType::health :{
         eid = factory.createCollectable(pos, "pngs/heart.png", 40.0);
         break;
      }
      case SpawnType::ammo: {
         eid = factory.createCollectable(pos, "pngs/ammo.png", 5.0);
         break;
      }
   }
   return eid;
}

void SpawnSys::update(EntityManager& g)
{
   for (auto& spw: g.getCmpVector<SpawnerCmp>()) 
   {
      if (g.isEntityAlive(spw.spawned_eid)) return;

      auto& phy = g.getRequiredCmpFromCmp<PhysicsCmp>(spw);
      switch (spw.status)
      {
         case SpawnStatus::idle: {
            spw.timer.start();
            std::printf("ToSpawn: %ld\n", spw.spawn_interval / spw.s);
            spw.status = SpawnStatus::waiting2spawn;
            break;
         }
         case  SpawnStatus::waiting2spawn:  {
            if (spw.timer.ellapsed_us() > spw.spawn_interval){
               std::printf("Spawning\n");
               spw.spawned_eid = SpawnNewEntity(spw.type, phy.pos);
               spw.status = SpawnStatus::idle;
               break;
            }
         }
      }
   }
}