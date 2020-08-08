//
// Created by Gabriel Chen on 8/6/20.
//

#include <string>
#include "Transform.h"
#include "variables.h"
#include "Sampler.h"

vec2 Sampler::pixelCoordToVirtualScreenPoint(int i, int j) {
  // According to spec, ray tracer uses center of pixel...
  double icenter = i + 0.5;
  double jcenter = j + 0.5;

  double fovyradians = (double) fovy * piConst / 180;
  double aspectratio = (double) w / h;
  double halfw = (double) w / 2;
  double halfh = (double) h / 2;
  double alpha = tan(fovyradians / 2) * aspectratio * ((jcenter - halfw) / halfw);
  double beta = tan(fovyradians / 2) * ((halfh - icenter) / (halfh));

  return vec2(alpha, beta);
}

Sampler::Sampler() {

}


