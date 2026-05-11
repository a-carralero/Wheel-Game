#pragma once

#include <cstdint>
#include <string_view>
#include "util/boolwithcooldown.hpp"
#include "util/timer.hpp"
#include "man/entitymanager.hpp"
#include "cmp/render.hpp"
#include "cmp/physics.hpp"
#include "util/vec2d.hpp"

struct DebugBoard
{
   double fps {60.0}, simfps {60.0};
   boolWithCoolDown pause {false, 1'000'000 / 3}; //0.33 cooldown
   bool showDegubCross = false;
   Timer timer;
};