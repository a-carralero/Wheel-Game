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

   ph.pos = pos;
   rn.loadFromFile(filename);
}

void Factory::
createEnemy(Vec2D pos, Vec2D target, const std::string_view filename)
{
   Entity& e = em.createEntity();
   auto& ph = em.addComponent<PhysicsCmp>(e);
   auto& rn = em.addComponent<RenderCmp>(e);
   auto& ai = em.addComponent<AiCmp>(e);

   ph.pos = pos;
   rn.loadFromFile(filename);
   ai.target = target;
   ai.tactive = true;
   ai.behaviour = SB::Arrive;
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
createCamera(Vec2D pos, uint32_t followEID){
   Entity& e = em.createEntity();
    auto& cam = em.addComponent<CameraCmp>(e);
    em.addComponent<PhysicsCmp>(e);
    cam.scrx = pos.x; cam.scry = pos.y;
    cam.followEntityID = followEID;
}



