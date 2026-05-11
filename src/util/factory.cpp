#include <array>
#include <fstream>
#include "util/factory.hpp"
#include "cmp/camera.hpp"
#include "picoJSON/picojson.hpp"


void Factory::
createCircle(Vec2D pos, const std::string_view filename)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
              em.addComponent<InputCmp>(e);
   auto& rn = em.addComponent<RenderCmp>(e);
   auto& cl = em.addComponent<ColliderCmp>(e);
   auto& st = em.addComponent<StatusCmp>(e);

   ph.pos = pos;
   rn.loadFromFile(filename);
   cl.type_mask = ColliderCmp::CT_Player;
   cl.against_mask = ColliderCmp::CT_Collectable | ColliderCmp::CT_Bullet;
   cl.AABB = {10.0, rn.w-10.0, 10.0, rn.h-10.0};
   st.health = 3.0;
   st.ammo = 10.0;
}

void Factory::
createEnemy(Vec2D pos, Vec2D target, const std::string_view filename)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
   auto& rn = em.addComponent<RenderCmp>(e);
   auto& ai = em.addComponent<AiCmp>(e);
   auto& cl = em.addComponent<ColliderCmp>(e);
   auto& st = em.addComponent<StatusCmp>(e);

   ph.pos = pos;
   rn.loadFromFile(filename);
   ai.target = target;
   ai.tactive = true;
   ai.behaviour = SB::Arrive;
   cl.type_mask = ColliderCmp::CT_Player;
   cl.against_mask = ColliderCmp::CT_Collectable | ColliderCmp::CT_Bullet;
   cl.AABB = {10.0, rn.w-10.0, 10.0, rn.h-10.0};
   st.health = 3.0;
   st.ammo = 10.0;
}

void Factory::
createCamera(Vec2D pos, uint32_t w, uint32_t h, uint32_t followEID)
{
    Entity& e = em.createEntity();
    auto& cam = em.addComponent<CameraCmp>(e);
    em.addComponent<PhysicsCmp>(e);
    cam.scrx = pos.x; cam.scry = pos.y;
    cam.w = w;    cam.h = h;
    cam.followEntityID = followEID;
}

void Factory::
createCamera(Vec2D pos, uint32_t followEID)
{
   Entity& e = em.createEntity();
   auto& cam = em.addComponent<CameraCmp>(e);
   em.addComponent<PhysicsCmp>(e);
   cam.scrx = pos.x; cam.scry = pos.y;
   cam.followEntityID = followEID;
}
   
void Factory::
createDebugEntity(Vec2D pos, std::string_view spritefile)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
   auto& rn = em.addComponent<RenderCmp>(e);
   ph.pos = pos;
   rn.loadFromFile(spritefile);
}

void Factory::createBullet(const PhysicsCmp& phy)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
   auto& rn = em.addComponent<RenderCmp>(e);
   auto& cl = em.addComponent<ColliderCmp>(e);
   auto& st = em.addComponent<StatusCmp>(e);

   rn.loadFromFile("pngs/bullet.png");

   double x = phy.pos.x + 12.0*(1.0 + std::cos(phy.orientation)) - 1.0 - (rn.w-1)/2.0;
   double y = phy.pos.y + 12.0*(1.0 + std::sin(phy.orientation)) - 1.0 - (rn.h-1)/2.0;
   ph.pos.x = x, ph.pos.y = y;
   ph.v_linear = 250.0;
   ph.v_max = 250.0;
   ph.drag = 0.0;

   cl.type_mask = ColliderCmp::CT_Bullet;
   cl.against_mask = ColliderCmp::CT_Player;
   cl.AABB = {1.0, rn.w-1.0, 1.0, rn.h-1.0};
   st.health = 50;
   st.lostHealthPerSecond = 10.0;
}

uint32_t Factory::
createCollectable(Vec2D pos, std::string_view spr, double value)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
   auto& rn = em.addComponent<RenderCmp>(e);
   auto& cl = em.addComponent<ColliderCmp>(e);

   ph.pos = pos;
   rn.loadFromFile(spr);
   cl.type_mask = ColliderCmp::CT_Collectable;
   cl.against_mask = ColliderCmp::CT_Player;
   cl.AABB = {1.0, rn.w-1.0, 1.0, rn.h-1.0};
   return e.getEntityID();
}

void Factory::
createSpawner(Vec2D pos, SpawnType type)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
   // auto& rn = em.addComponent<RenderCmp>(e);
   // auto& cl = em.addComponent<ColliderCmp>(e);
   auto& spw = em.addComponent<SpawnerCmp>(e);

   ph.pos = pos;
   // rn.loadFromFile("pngs/spawner.png");
   // cl.AABB = {1.0, rn.w-1.0, 1.0, rn.h-1.0};
   // cl.type_mask = ColliderCmp::CT_Collectable;
   // cl.against_mask = ColliderCmp::CT_Player;
   spw.type = type;
   if (type == SpawnType::ammo)
      spw.spawn_interval = 15'000'000;
   else
      spw.spawn_interval = 20'000'000;

}