#pragma once
#include <cstdint>

struct EntityManager;

struct RenderSys_TinyPTC
{
   RenderSys_TinyPTC();
   ~RenderSys_TinyPTC();
   void prerender();
   void update(EntityManager& em, uint32_t* screen);
};