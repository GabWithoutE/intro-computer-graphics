//
// Created by Gabriel Chen on 8/6/20.
//

#ifndef HW3_RAY_H
#define HW3_RAY_H

#include <glm/glm.hpp>

using namespace glm;

class Ray {
public:
  float deltaU;
  float deltaV;
  vec3 p0;
  vec3 p1;
  Ray(float deltaU, float deltaV, vec3 p1, vec3 p0);
};

#endif //HW3_RAY_H
