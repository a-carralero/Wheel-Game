#pragma once
#include <cstdint>
#include <memory>
#include <cstring>
#include <cmath>
#include <cassert>

#include "cmp/render.hpp"
#include "cmp/collider.hpp"
#include "cmp/physics.hpp"
#include "cmp/camera.hpp"
#include "util/box.hpp"
#include "man/entitymanager.hpp"
#include "util/constants.hpp"



struct CameraWithPhysics{
  const CameraCmp* cam = nullptr;
  const PhysicsCmp* phy = nullptr;
};


template <typename Backend>
struct RenderSys 
{   
 private:
   Backend backend {};
   std::unique_ptr<uint32_t[]> m_screen {nullptr};
   mutable CameraWithPhysics m_currentCam;

   static constexpr uint32_t kR = 0x00FF0000;
   static constexpr uint32_t kG = 0x0000FF00;
   static constexpr uint32_t kB = 0x000000FF;
   static constexpr uint32_t kWhite = 0x00FFFFFF;
   static constexpr uint32_t kBlack = 0x00000000;


   uint32_t* getScreenXY(uint32_t x, uint32_t y) const {
      uint32_t* screen =  m_screen.get() + x + KWIDTH*y;
      return screen;
   }

   void clearScreen(){
      uint32_t* screen = m_screen.get();
      uint32_t size = KWIDTH*KHEIGHT;
      std::fill(screen, screen+size, kWhite);
   }
   
   void drawEntity(const RenderCmp& rn, const PhysicsCmp& phy) {
      uint32_t* screen = getScreenXY(phy.pos.x, phy.pos.y);
      const uint32_t* spr = rn.sprite.data();
      for (uint32_t y=0; y< rn.h; ++y){
         std::memcpy(screen, spr, rn.w*sizeof(uint32_t));
         screen += KWIDTH;
         spr += rn.w;
      }
   }

   void renderFilledBox(const Box_t<uint32_t>& box, uint32_t color) const{
   // Crop function
      auto crop = [](uint32_t &val, uint32_t max, uint32_t inf) {
         if (val > inf) val = 0;
         else if (val > max) val = max;
      };

      // Infinite values to be considered negatives
      uint32_t xinf = 4*KWIDTH;
      uint32_t yinf = 4*KHEIGHT;

      uint32_t xL = box.xleft();
      uint32_t xR = box.xright();
      uint32_t yU = box.yup();
      uint32_t yD = box.ydown();

      // Crop line to screen limits
      crop(xL, KWIDTH, xinf);
      crop(xR, KWIDTH, xinf);
      crop(yU, KHEIGHT, yinf);
      crop(yD, KHEIGHT, yinf);

      if (xL == KWIDTH || xR == 0 
         || yU == KHEIGHT || yD == 0) return;
      
      const uint32_t width = box.w;
      uint32_t height = box.h;
      uint32_t* screen = getScreenXY(xL, yU);

      while (height--)
      {
         for (uint32_t i=0; i<width; ++i){
            screen[i] = color; 
         }
         screen += KWIDTH;
      }
   }

   void drawClippedSprite(const RenderCmp& rn, const PhysicsCmp& phy) const{
      // SPRITE -> WORLD -> CAMERA -> SCREEN
      //      +pos    -poscam    +poscamscr

      if (!m_currentCam.phy || !m_currentCam.cam){
         std::cerr << "Coordenadas de camara no definidas\n";
         std::terminate();
      }
      auto& CamScr = *m_currentCam.cam;
      auto& CamPhy = *m_currentCam.phy;

      struct {
      Box<double> world {};
      Box<double> camera {};
      Box<uint32_t> crop {};
      struct {
         uint32_t x, y, w, h;
         } screen;
      } spr;

      spr.world = {
         phy.pos.x      , 
         phy.pos.x +rn.w , 
         phy.pos.y       , 
         phy.pos.y +rn.h
      }; 

      spr.camera = {
         spr.world.xL - CamPhy.pos.x,
         spr.world.xR - CamPhy.pos.x,
         spr.world.yU - CamPhy.pos.y,
         spr.world.yD - CamPhy.pos.y,
      };

      // SPRITE CLIPPING
      if (  spr.camera.xR < 0 || spr.camera.xL > CamScr.w 
         || spr.camera.yD < 0 || spr.camera.yU > CamScr.h )
         return;
      
      // SPRITE CROPPING
      spr.crop = {
         static_cast<uint32_t>(std::round((spr.camera.xL < 0)         ? -spr.camera.xL : 0 )),
         static_cast<uint32_t>(std::round((spr.camera.xR > CamScr.w ) ? spr.camera.xR - CamScr.w  : 0 )),
         static_cast<uint32_t>(std::round((spr.camera.yU < 0)         ? -spr.camera.yU : 0 )),
         static_cast<uint32_t>(std::round((spr.camera.yD > CamScr.h)  ? spr.camera.yD - CamScr.h : 0)) 
      };
      
      spr.screen = {
         static_cast<uint32_t>(std::round(spr.camera.xL + CamScr.scrx)) + spr.crop.xL,
         static_cast<uint32_t>(std::round(spr.camera.yU + CamScr.scry)) + spr.crop.yU,
         rn.w - spr.crop.xL - spr.crop.xR ,
         rn.h - spr.crop.yU - spr.crop.yD        
      };

      // Draw Sprite
      uint32_t* screen = getScreenXY(spr.screen.x, spr.screen.y);
      const uint32_t* sprite = rn.sprite.data() + static_cast<uint32_t>(spr.crop.yU*rn.w + spr.crop.xL);
      while (spr.screen.h--){
         for (uint32_t i = 0; i < spr.screen.w; ++i) {
               // draw only if transperency != 0
               if ( *sprite & 0xFF000000 ) 
                  *screen = *sprite;
               sprite++;
               screen++;
         }
         sprite += rn.w - spr.screen.w;
         screen += KWIDTH - spr.screen.w;
      }

      
   }

   void drawBox(const RenderCmp& rn, const PhysicsCmp& phy) const
   {
      // draw box
      double bw = 20; // ancho y alto del box
      // obtenemos las coordenadas del centro del sprite
      double sprx_center = phy.pos.x + static_cast<double>(rn.w-1)/2.0;
      double spry_center = phy.pos.y + static_cast<double>(rn.h-1)/2.0;
      // obtenemos las coordenadas del centro del box respecto al centro del sprite
      double box_center_x = static_cast<double>(rn.w)/2.0;
      double box_center_y = 0.0;
      // obtenemos las coordenadas del centro del box respecto al centro del sprite después de la rotación
      double box_x_rot = box_center_x*std::cos(phy.orientation) - box_center_y*std::sin(phy.orientation);
      double box_y_rot = box_center_x*std::sin(phy.orientation) + box_center_y*std::cos(phy.orientation);
      // hacemos la traslación
      double box_x = box_x_rot + sprx_center;
      double box_y = box_y_rot + spry_center;
      // debemos obtener el punto xleft, yup del box
      uint32_t box_xleft = box_x - (bw-1.0)/2.0;
      uint32_t box_yup   = box_y - (bw-1.0)/2.0;
      
      uint32_t boxw = static_cast<uint32_t>(bw);
      Box_t<uint32_t> lead {box_xleft, box_yup, boxw, boxw};
      renderFilledBox(lead, kR);
   }

   void drawAllEntities(const EntityManager& g) const {
      for(const auto& rn: g.getCmpVector<RenderCmp>()){
         const Entity& e = g.getEntityByID(rn.getEntityID());
         auto& phy = e.getComponent<PhysicsCmp>();
         drawClippedSprite(rn, phy);

         auto& col = e.getComponent<ColliderCmp>();
         uint8_t type = col.type_mask;
         if (type == ColliderCmp::ColliderType::CT_Player)
            drawBox(rn, phy);
      }
   }
   
   void drawAllCameras(const EntityManager& g) const {
      for(const auto& cam: g.getCmpVector<CameraCmp>()) {
         auto& phy = g.getRequiredCmpFromCmp<PhysicsCmp>(cam);
         m_currentCam.cam = &cam;
         m_currentCam.phy = &phy;
         drawAllEntities(g);
      }
   }

 public:
   RenderSys() 
      : m_screen (std::make_unique<uint32_t[]>(KWIDTH*KHEIGHT)) {   
   }

   void update(EntityManager& g)
   {
      clearScreen();
      backend.prerender();
      drawAllCameras(g);
      backend.update(g, m_screen.get());
   }
};

