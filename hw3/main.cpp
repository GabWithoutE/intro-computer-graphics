/******************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi  */
/* Extends HW 1 to deal with shading, more transforms and multiple objects    */
/******************************************************************************/

// You shouldn't have to edit this file at all!

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h"
#include <FreeImage.h>

using namespace std; 

// Main variables in the program.  
#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h" // prototypes for readfile.cpp
#include "Camera.h"
#include "Sampler.h"
#include "Raytracer.h"

void saveScreenshot(BYTE * pixels, string outputfilename) {
  FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

  std::cout << "Saving screenshot: " << outputfilename << "\n";

  FreeImage_Save(FIF_PNG, img, outputfilename.c_str(), 0);
}

void init() {

}

void trackProgress(int totalpixels, int * currentpixel) {
  int currentprogress = (*currentpixel / totalpixels) * 100; // current progress in percent
  printf("Done %i %%\n", currentprogress);
}

int main(int argc, char* argv[]) {
//  BYTE *pixels = new BYTE[3*totalpixels];
  readfile(argv[1]);
  vec3 colors[totalpixels];
  BYTE pixels[3*totalpixels];
//
////  cout << "Hello: " << 3 * totalpixels;
//
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
//  for (int i = 0; i < 1; i++) {
//    for (int j = 0; j < 1; j++) {
      // restart the current depth for each pixel to avoid excessive recursive raytracing...
      int currentdepth = 0;
      vec2 virtualscreenpoint = Sampler::pixelCoordToVirtualScreenPoint(i, j);
      Ray ray = Camera::createRay(virtualscreenpoint);
      vec3 color = Raytracer::traceRay(ray, currentdepth);
      colors[i * w + j] = color;
    }
  }

  for (int i = 0; i < totalpixels; i++) {
//    // the way they read pixels is backwards, so r is 2, g is y 1, b is 0
    pixels[i * 3 + 0] = colors[i].z;
    pixels[i * 3 + 1] = colors[i].y;
    pixels[i * 3 + 2] = colors[i].x;
  }
//
//
  if (fname.empty()) {
    saveScreenshot(pixels, "Untitled.png");
  } else {
    saveScreenshot(pixels, fname);
  }
  return 0;
}
