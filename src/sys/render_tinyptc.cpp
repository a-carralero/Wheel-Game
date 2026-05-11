#include "sys/render_tinyptc.hpp"
#include "util/constants.hpp"
extern "C"{ 
   #include "tinyPTC/src/tinyptc.h"
}

RenderSys_TinyPTC::RenderSys_TinyPTC()
{
   ptc_open("window", KWIDTH, KHEIGHT);
}

RenderSys_TinyPTC::~RenderSys_TinyPTC()
{
   ptc_close();
}


void RenderSys_TinyPTC::prerender()
{
   // Do nothing
}

void RenderSys_TinyPTC::update(EntityManager& em, uint32_t* screen)
{
   ptc_update(screen);
}