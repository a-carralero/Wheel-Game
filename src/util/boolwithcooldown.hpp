#pragma once
#include "util/timer.hpp"

struct boolWithCoolDown
{
   boolWithCoolDown(bool v, int64_t micros) 
      : value(v), coolDownMicros(micros) {} 

   bool value = false;
   const int64_t coolDownMicros = 1'000'000; // 1s
   Timer timer;
   bool toggle() {
      if (timer.ellapsed_us() > coolDownMicros){
         timer.start();
         value = !value;
      }
      return value;
   }
};
