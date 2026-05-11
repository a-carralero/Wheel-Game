#pragma once
#include "util/timer.hpp"

struct RangedTimer: Timer
{
   int64_t min_us = 0;
   int64_t max_us = 0;
   int64_t target_us = 0;

   RangedTimer(int64_t t1, int64_t t2)
      : min_us(t1), max_us(t2) {
      start();
   }

};