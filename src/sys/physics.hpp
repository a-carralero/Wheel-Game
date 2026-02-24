#pragma once

struct EntityManager;

struct PhysicsSys 
{
   void update(EntityManager& g, double dt) const;
};

