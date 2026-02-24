#pragma once
#include <iostream>
#include <cstdint>
#include "sys/render.hpp"
#include "sys/physics.hpp"
#include "sys/input.hpp"
#include "sys/camera.hpp"
#include "sys/ai.hpp"
#include "man/entitymanager.hpp"
#include "util/factory.hpp"
#include "util/timer.hpp"
#include "man/state_base.hpp"
#include "util/constants.hpp"


class Game: public StateBase
{
   EntityManager EntityMan;
   Factory factory{EntityMan};
   RenderSys Render;
   PhysicsSys Physics;
   InputSys Input;
   CameraSys Camera;
   AiSys Ai;

public:

   Game()
   {
      factory.createCamera({0,0});
      factory.createCircle({640, 360}, "pngs/blueCircle50x50.png");
      factory.createEnemy({640, 500}, {640, 360}, "pngs/orangeCircle50x50.png");
   }

   void update() override
   {
      Timer timer;
      timedCall("Camera", Camera.update(EntityMan));
      timedCall("Input", Input.update(EntityMan));
      timedCall("Physics", Physics.update(EntityMan, 1.0/static_cast<double>(FPS)));
      timedCall("Ai", Ai.update(EntityMan, 1.0/static_cast<double>(FPS)));
      timedCall("Render", Render.update(EntityMan));
      if (Input.isKeyPressed(XK_Escape)) alive = false;
      // std::cout << "[Towait] " << timer.waitUntil_us(USPF) << "\n";
      timer.waitUntil_us(USPF);
      timer.start();
   }
};