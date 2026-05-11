#pragma once
#include <cstdint>
#include "cmp/component.hpp"
#include "util/keysyms.hpp"

struct InputCmp: Component<InputCmp>
{
   explicit InputCmp(uint32_t eid)
      : Component(eid) {}
   
   KeySym left  { KS_O };
   KeySym right { KS_P };
   KeySym up    { KS_Q };
   // KeySym down  { KS_R };
   KeySym arrive { KS_A };
   KeySym seek   { KS_S };
   KeySym pursue { KS_R };
   KeySym path_following { KS_F };
   KeySym space  {KS_SPACE};
};