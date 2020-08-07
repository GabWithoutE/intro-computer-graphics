//
// Created by Gabriel Chen on 8/6/20.
//

#ifndef HW3_CAMERA_H
#define HW3_CAMERA_H

#include "Ray.h"

class Camera {
  static Ray createRay(vec2 virtualscreenpixel);
};


#endif //HW3_CAMERA_H
