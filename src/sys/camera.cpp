#include "sys/camera.hpp"
#include "man/entitymanager.hpp"
#include "cmp/camera.hpp"
#include "cmp/physics.hpp"
#include "cmp/render.hpp"


void CameraSys::update(EntityManager& g) const 
{
   for(auto& cam: g.getCmpVector<CameraCmp>())
   {
      if (cam.followEntityID == INVALID_EID) continue;
      auto& entity = g.getEntityByID(cam.followEntityID);
      auto& entphy = entity.getComponent<PhysicsCmp>();
      auto& camphy = g.getRequiredCmpFromCmp<PhysicsCmp>(cam);

      auto& renent = entity.getComponent<RenderCmp>();
      uint32_t rw = renent.w; 
      uint32_t rh = renent.h;

      camphy.pos.x = entphy.pos.x - ( cam.w - rw) / 2;
      camphy.pos.y = entphy.pos.y - ( cam.h - rh) / 2;
   }
}
