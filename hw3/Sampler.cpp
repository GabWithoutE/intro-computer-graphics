//
// Created by Gabriel Chen on 8/6/20.
//

#include "Sampler.h"
#include "variables.h"

vec2 Sampler::pixelToNormalizedPoint(int i, int j) {
  // According to spec, ray tracer uses center of pixel...
  float icenter = i + 0.5;
  float jcenter = j + 0.5;

  float fovyradians = fovy * pi / 180;
  float aspectratio = (float) (w / h);
  float halfw = (float) w / 2;
  float halfh = (float) h / 2;
  float alpha = tan(fovyradians / 2) * aspectratio * ((jcenter - halfw) / halfw);
  float beta = tan(fovyradians / 2) * ((halfh - icenter) / (halfh));

  return vec2(alpha, beta);
}

Sampler::Sampler() {

}
