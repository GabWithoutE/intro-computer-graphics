//
// Created by Gabriel Chen on 8/6/20.
//

#include "Camera.h"
#include "variables.h"

Ray Camera::createRay(vec2 virtualscreenpixel) {
  vec3 unitW = normalize(eye - center);
  vec3 unitU = normalize(cross(up, unitW));
  vec3 unitV = normalize(cross(unitW, unitV));

  return {
    virtualscreenpixel.x,
    virtualscreenpixel.y,
    normalize(virtualscreenpixel.x * unitU + virtualscreenpixel.y * unitV - unitW),
    eye
  };
}