#include <math.h>
#include <numbers>
#include <algorithm>
#include "util/controller.hpp"

double calcDistance(Vec2D posref, Vec2D pos)
{
   Vec2D err = posref - pos;
   double dist = std::sqrt(err.x*err.x + err.y*err.y);
   return dist;
}

double 
linearVelControl(Vec2D posref, Vec2D pos, double kp, double min, double max)
{
   double err_dist = calcDistance(posref, pos);
   double vel = err_dist* kp;
   vel = std::clamp(vel, min, max);
   return vel;
}

double 
accelerationControl(double velref, double vel, double kp, double min, double max)
{
   double vel_err = velref - vel;
   double acc = vel_err * kp;
   acc = std::clamp(acc, min, max);
   return acc;
}

double calcAngleTarget (Vec2D posref, Vec2D pos)
{
   constexpr double PI = std::numbers::pi;
   Vec2D dist = posref - pos;
   double theta = std::atan2(dist.y, dist.x);
   if (theta < 0) theta +=2*PI;
   return theta;
}

double 
orientationControl(double theta_ref, double theta, double kp, double min, double max)
{
   double err_theta = theta_ref - theta;
   // queremos que etheta se mantenta entre [-pi, pi];
   err_theta = std::atan2(sin(err_theta), cos(err_theta));
   double v_angular = err_theta * kp;
   v_angular = std::clamp(v_angular, min, max);
   return v_angular;
}