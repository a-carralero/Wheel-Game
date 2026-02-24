#pragma once
#include <concepts>

template <typename T>
concept Numerical = std::integral<T> || std::floating_point<T>;

template <Numerical T>
struct Box{
   T x = 0, y = 0;
   T w = 0, h = 0;
   constexpr T xleft() const   {return x; }
   constexpr T xright() const  {return x + w-1;}
   constexpr T yup() const     {return y; }
   constexpr T ydown() const   {return y + h-1; }
   constexpr T xcenter() const {return x + (w-1)/2;}
   constexpr T ycenter() const {return y + (h-1)/2; }
};