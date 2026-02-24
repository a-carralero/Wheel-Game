// #include <cmath>
// #include <iostream>
// #include "sys/collision.hpp"
// #include "man/entitymanager.hpp"
// #include "cmp/physics.hpp"
// #include "cmp/health.hpp"
// #include "util/constants.hpp"

// void CollisionSys::update(EntityManager& g) const 
// {
//    auto& collider_vec = g.getComponents<ColliderCmp>();

//    for(auto&c : collider_vec) setFalseCollideds(c.boxRoot);

//    std::size_t size = collider_vec.size();
//    for (std::size_t i=0; i<size; ++i)
//    {
//       auto& cl = collider_vec[i];
//       auto* phy = g.getRequiredCmpFromCmp<PhysicsCmp>(cl);
//       if (!phy) continue;
//       if (cl.mask & ColliderCmp::L_Boundaries)
//          checkBoundaries(cl, *phy);

//       for (std::size_t j=i+1; j<size; ++j){
//          auto& cl2 = collider_vec[j];
//          if ((cl.mask & cl2.mask) == 0) continue;
//          auto* phy2 = g.getRequiredCmpFromCmp<PhysicsCmp>(cl2);
//          if (!phy) continue;
//          if (checkObjCollision(cl.boxRoot, *phy, cl2.boxRoot, *phy2)){
//             react2Collision(g, cl, cl2);
//          }
//       }

//       // if (phy->gravity > 0){
//       //    std::cout << "Collision: vx = " << phy->vx << "\n";
//       // }
//    }
   
// }

// void 
// CollisionSys::checkBoundaries(const ColliderCmp& cl, 
//                                     PhysicsCmp& phy) const
// {
//    auto [xl, xr, yu, yd] = move2WorldFrame(cl.boxRoot.box, phy.pos.x, phy.pos.y);
// }


// BoundingBox<float> CollisionSys::
// move2WorldFrame(const BoundingBox<uint32_t>& box, float x, float y) const
// {
//    return BoundingBox<float> {
//       x + box.xL,
//       x + box.xR,
//       y + box.yU,
//       y + box.yD,
//    };
// }

// bool 
// CollisionSys::checkObjCollision(BoundingBoxNode& bn1, PhysicsCmp& phy1,
//                                 BoundingBoxNode& bn2, PhysicsCmp& phy2) const
// {
//    return false;
// }

// void 
// CollisionSys::setFalseCollideds(BoundingBoxNode& bn) const
// {
//    bn.collided = false;
//    for (auto& child : bn.childs)
//       setFalseCollideds(child);
// }

// void
// CollisionSys::react2Collision(EntityManager& g,
//                               ColliderCmp& c1, ColliderCmp& c2) const
// {

// }



// void CollisionSys::
// undoCollision(EntityManager& g, const ColliderCmp& mobile, 
//                                 const ColliderCmp& solid) const
// {

// }


// const BoundingBoxNode&
// CollisionSys::leafNodeCollided(const BoundingBoxNode& bn) const
// {
//    if(!bn.childs.empty())
//    {
//       for (auto& child : bn.childs){
//          if (child.collided){
//             return leafNodeCollided(child);
//          }
//       }
//       std::cerr << "Error lógico, no se encontró ningún hijo que colisione";
//       std::terminate();
//    }
//    else{
//       return bn;
//    }
// }