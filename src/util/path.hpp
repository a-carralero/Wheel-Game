#pragma once
#include <cstdint>
#include <array>
#include <cassert>
#include "util/vec2d.hpp"

template <std::size_t N>
struct Path
{
 private:
   Vec2D waypoints[N] = {};
   std::size_t m_size = 0;
   std::size_t index = 0;

 public:
   template <typename... Args>
   Path(Args&&... args)
      : waypoints{std::forward<Args>(args)...}
      , m_size(sizeof...(Args)) {}

   std::size_t size() const {return m_size; }
   Vec2D& waypoint() {
      assert(m_size > 0);
      return waypoints[index];
   }
   void next(){
      if (m_size == 0) return;
      index++;
      if (index >= m_size)
         index = 0;
   }

   using iterator = const Vec2D*;  
   iterator begin() const { return waypoints;          } 
   iterator end()   const { return waypoints + m_size; }  // el elemento después del último
};

template <typename ...Args>
Path(Args&&...) -> Path<sizeof...(Args)>;