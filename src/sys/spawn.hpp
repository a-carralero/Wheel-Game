#pragma once
#include <cstdint>
#include <string_view>
#include "cmp/entity.hpp"
#include "cmp/spawner.hpp"
#include "util/vec2d.hpp"
#include "util/factory.hpp"

struct EntityManager;

struct SpawnSys 
{
   void update(EntityManager& g);
   SpawnSys(Factory& f) : factory(f) {}

 private:
   Factory& factory;
   uint32_t SpawnNewEntity(SpawnType type, Vec2D pos);  
};

