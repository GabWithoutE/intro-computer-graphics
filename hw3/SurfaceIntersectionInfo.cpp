//
// Created by Gabriel Chen on 8/8/20.
//

#include "SurfaceIntersectionInfo.h"

SurfaceIntersectionInfo::SurfaceIntersectionInfo(
  int objectindex,
  float intersectdepth,
  vec3 normal,
  vec3 pointofintersection,
  vec3 directionin
) {
  this->objectindex=objectindex;
  this->intersectdepth=intersectdepth;
  this->normal=normal;
  this->pointofintersection=pointofintersection;
  this->directionin=directionin;
}
