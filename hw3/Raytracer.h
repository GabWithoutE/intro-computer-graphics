//
// Created by Gabriel Chen on 8/6/20.
//

#ifndef HW3_RAYTRACER_H
#define HW3_RAYTRACER_H

#include "Ray.h"
#include "glm/glm.hpp"
using namespace glm;

class Raytracer {
public:
  static vec3 traceRay(Ray ray, int &currentdepth);
  Raytracer();
};


#endif //HW3_RAYTRACER_H
