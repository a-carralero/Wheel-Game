#pragma once
#include <cstdint>
#include <chrono>
#include <functional>
#include "cmp/component.hpp"
#include "util/rangedtimer.hpp"

enum class SpawnType{
   health ,
   ammo
};

enum class SpawnStatus{
   idle ,         // An entity has been created. Idle until the entity is picked
   waiting2spawn  // Waiting before the creation of a new entity
};

struct SpawnerCmp: Component<SpawnerCmp>
{
   explicit SpawnerCmp(uint32_t eid)
      : Component(eid) {}
   
   using clk = std::chrono::steady_clock;

   SpawnType type = SpawnType::health;       // Type of obect to be spawned
   SpawnStatus status = SpawnStatus::idle;   // Initially in idle status
   uint32_t spawned_eid = INVALID_EID;                 // EID of the last entity spawaned
   static constexpr int64_t s = 1'000'000;   // Same second definition as in RangedTimer
   //RangedTimer timer {10*s, 20*s};         // Spawn each 10-20 seconds with a gaussian probability mean 15
   Timer timer {};
   int64_t spawn_interval = 15*s;

};