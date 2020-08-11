//
// Created by Gabriel Chen on 8/6/20.
//

#ifndef HW3_RAYTRACERA_H
#define HW3_RAYTRACERA_H

#include "Ray.h"
#include "glm/glm.hpp"
using namespace glm;

//vec3 castRay(Ray ray, int currentdepth);

class RaytracerA {
public:
  static vec3 traceRay(Ray ray);
  RaytracerA();
};


#endif //HW3_RAYTRACERA_H
