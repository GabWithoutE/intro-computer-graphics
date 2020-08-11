//
// Created by Gabriel Chen on 8/8/20.
//

#ifndef HW3_SURFACEINTERSECTIONINFO_H
#define HW3_SURFACEINTERSECTIONINFO_H

#include "Transform.h"

class SurfaceIntersectionInfo {
public:
  int objectindex;
  float intersectdepth;
  vec3 normal;
  vec3 pointofintersection;
  vec3 directionin;
  SurfaceIntersectionInfo(int objectindex, float intersectdepth, vec3 normal, vec3 pointofintersection, vec3 directionin);
};

#endif //HW3_SURFACEINTERSECTIONINFO_H
