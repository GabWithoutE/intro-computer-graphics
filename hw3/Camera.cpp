//
// Created by Gabriel Chen on 8/6/20.
//

#include "Camera.h"
#include "variables.h"

Ray Camera::createRay(vec2 virtualscreenpixel) {
  vec3 unitW = normalize(eye - center);
  vec3 unitU = normalize(cross(unitW, up));
  vec3 unitV = normalize(cross(unitW, unitU));
  vec3 p1 = normalize(virtualscreenpixel.x * unitU + virtualscreenpixel.y * unitV - unitW);
//  printf("unitW: %f, %f, %f\n", unitW.x, unitW.y, unitW.z);
//  printf("unitU: %f, %f, %f\n", unitU.x, unitU.y, unitU.z);
//  printf("unitV: %f, %f, %f\n", unitV.x, unitV.y, unitV.z);
//  printf("p1: %f, %f, %f\n", p1.x, p1.y, p1.z);

  return Ray(
    virtualscreenpixel.x,
    virtualscreenpixel.y,
    p1,
    eye
  );
}

Camera::Camera() {

}
