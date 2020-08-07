//
// Created by Gabriel Chen on 8/6/20.
//

#include <glm/vec2.hpp>
#include "Transform.h"

class Sampler {
public:
  Sampler();

  // PixelToNormalizedPoint: computes and returns the virtual screen point given the pixel indices
  static vec2 pixelToNormalizedPoint(int i, int j);
};


