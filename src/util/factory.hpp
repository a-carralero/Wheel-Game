#pragma once
#include <cstdint>
#include <string_view>
#include "man/entitymanager.hpp"
#include "cmp/physics.hpp"
#include "cmp/render.hpp"
#include "cmp/input.hpp"
#include "cmp/collider.hpp"
#include "cmp/spawner.hpp"
#include "cmp/status.hpp"
#include "cmp/ai.hpp"
#include "util/vec2d.hpp"

struct EntityManager;

struct Factory
{
private:
   EntityManager& em;
public:

   Factory(EntityManager& eman) : em(eman) {}
   void createCircle(Vec2D pos, const std::string_view filename);
   void createEnemy(Vec2D pos, Vec2D target, const std::string_view filename);
   void loadLevelJson(std::string_view filepath);
   void createCamera(Vec2D pos, uint32_t w, uint32_t h, uint32_t followEID=-1);
   void createCamera(Vec2D pos, uint32_t followEID=-1);
   void createDebugEntity(Vec2D pos, std::string_view spritefile);
   void createBullet(const PhysicsCmp& phy);
   uint32_t createCollectable(Vec2D pos, std::string_view spr, double value);
   void createSpawner(Vec2D pos, SpawnType type);
};