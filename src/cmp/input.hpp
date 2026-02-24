#pragma once
#include <cstdint>
#include "cmp/component.hpp"
#include <X11/X.h>
#include <X11/keysym.h>

struct InputCmp: Component<InputCmp>
{
   explicit InputCmp(uint32_t eid)
      : Component(eid) {}
   
   KeySym left  { XK_o };
   KeySym right { XK_p };
   KeySym up    { XK_q };
   KeySym down  { XK_a };
   KeySym seek  { XK_s };
   KeySym pursue{ XK_r };
   KeySym path_following { XK_f };
};