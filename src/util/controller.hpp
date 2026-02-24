#pragma once
#include "util/vec2d.hpp"


double calcDistance(Vec2D posref, Vec2D pos);
double linearVelControl(Vec2D posref, Vec2D pos, double kp, double min, double max);
double accelerationControl(double velref, double vel, double kp, double min, double max);
double orientationControl(double theta_ref, double theta, double kp, double min, double max);
double calcAngleTarget (Vec2D posref, Vec2D pos);