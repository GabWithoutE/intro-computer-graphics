//
// Created by Gabriel Chen on 8/6/20.
//

#include "Ray.h"

Ray::Ray(float deltaU, float deltaV, vec3 p1, vec3 p0) {
  this->deltaU = deltaU;
  this->deltaV = deltaV;
  this->p1 = p1;
  this->p0 = p0;
}