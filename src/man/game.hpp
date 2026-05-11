#pragma once
#include <iostream>
#include <cstdint>

#include "sys/render.hpp"
#include "sys/physics.hpp"
#include "sys/input.hpp"
#include "sys/camera.hpp"
#include "sys/ai.hpp"
#include "sys/collision.hpp"
#include "sys/status.hpp"
#include "sys/spawn.hpp"

#include "man/state_base.hpp"
#include "man/entitymanager.hpp"
#include "util/factory.hpp"
#include "util/timer.hpp"
#include "util/constants.hpp"


#ifdef USE_IMGUI_GLFW
#include "sys/input_imgui.hpp"
#include "sys/render_imgui.hpp"
#else
#include "sys/input_tinyptc.hpp"
#include "sys/render_tinyptc.hpp"
#endif


class Game: public StateBase
{
   EntityManager EntityMan;
   Factory factory{EntityMan};
   PhysicsSys Physics;
   CameraSys Camera;
   AiSys Ai;
   CollisionSys Collision;
   StatusSys Status;
   SpawnSys Spawn{factory};

#ifdef USE_IMGUI_GLFW
   RenderSys<RenderSys_ImGui> Render;
   InputSys<InputSys_ImGui> Input{factory};
#else
   RenderSys<RenderSys_TinyPTC> Render;
   InputSys<InputSys_TinyPTC> Input{factory};
#endif


public:

   Game()
   {
      factory.createCamera({0,0});
      factory.createCircle({640, 360}, "pngs/blueCircle50x50.png");
      factory.createEnemy({640, 500}, {640, 360}, "pngs/orangeCircle50x50.png");
      factory.createSpawner({400,400}, SpawnType::health);
      factory.createSpawner({200,200}, SpawnType::ammo);
   }

   void update() override
   {
      DebugBoard& dbg = EntityMan.getDebugBoard();
      int64_t micros {static_cast<int64_t>(1'000'000.0 /dbg.fps)};

      timedCall("Render", Render.update(EntityMan));
      timedCall("Input", Input.update(EntityMan));
      
      if (!dbg.pause.value && dbg.timer.ellapsed_us() > micros)
      {
         double dt { 1.0/dbg.simfps };
         timedCall("Camera", Camera.update(EntityMan));
         timedCall("Collision", Collision.update(EntityMan));
         timedCall("Physics", Physics.update(EntityMan, dt));
         timedCall("Ai", Ai.update(EntityMan, dt));
         timedCall("Status", Status.update(EntityMan, dt));
         timedCall("Spawn", Spawn.update(EntityMan));
         dbg.timer.start();
      }
      
      if (Input.isExitKeyPressed()) alive = false;

   }
};