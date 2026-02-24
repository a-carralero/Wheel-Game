#pragma once

struct Vec2D
{
   double x {0.0}, y {0.0};

   Vec2D operator+(const Vec2D& v) const{
      return {x+v.x, y+v.y};
   }
   Vec2D operator-(const Vec2D& v) const {
      return {x-v.x, y-v.y};
   }
   Vec2D& operator+=(const Vec2D& v){
      x += v.x;
      y += v.y;
      return *this;
   }
   Vec2D& operator-=(const Vec2D& v){
      x -= v.x;
      y -= v.y;
      return *this;
   }
   Vec2D operator*(double k) const{
      return {x*k, y*k};
   }
};