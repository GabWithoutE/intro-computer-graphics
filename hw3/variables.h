/*****************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi */
/* Extends HW 1 to deal with shading, more transforms and multiple objects   */
/*****************************************************************************/

// This is the basic include file for the global variables in the program.  
// Since all files need access to it, we define EXTERN as either blank or 
// extern, depending on if included in the main program or not.

#include <string>

#ifdef MAINPROGRAM
#define EXTERN 
#else 
#define EXTERN extern 
#endif


EXTERN int amount; // The amount of rotation for each arrow press
EXTERN vec3 eye; // The (regularly updated) vector coordinates of the eye 
EXTERN vec3 up;  // The (regularly updated) vector coordinates of the up 

#ifdef MAINPROGRAM 
vec3 eyeinit(0.0,0.0,5.0) ; // Initial eye position, also for resets
vec3 upinit(0.0,1.0,0.0) ; // Initial up position, also for resets
vec3 center(0.0,0.0,0.0) ; // Center look at point 
int amountinit = 5;
int w = 500, h = 500, totalpixels = 250000 ; // width and height and totalpixels
float fovy = 90.0 ; // For field of view
float maxdepth = 5 ;
string fname;
#else 
EXTERN vec3 eyeinit ; 
EXTERN vec3 upinit ; 
EXTERN vec3 center ;
EXTERN int amountinit;
EXTERN int w, h, totalpixels ;
EXTERN float fovy ; 
EXTERN float maxdepth ;
EXTERN std::string fname ;
#endif

EXTERN mat4 projection, modelview; // The mvp matrices
EXTERN uint projectionPos, modelviewPos; // Uniform locations of the above matrices
static enum {view, translate, scale} transop ; // which operation to transform 
enum shape {cube, sphere, teapot, triangle} ;
EXTERN float sx, sy ; // the scale in x and y 
EXTERN float tx, ty ; // the translation in x and y

// Lighting parameter array, similar to that in the fragment shader
enum light {point, directional};
const int numLights = 100 ;
EXTERN float lightposn [3*numLights] ; // Light Positions
EXTERN float lightcolor[3*numLights] ; // Light Colors
EXTERN light lighttype[numLights] ;
EXTERN float lightransf[4*numLights] ; // Lights transformed by modelview
EXTERN int lightsused ;                     // How many lights are used
EXTERN float attenuation[3] ;

// Materials (read from file) 
// With multiple objects, these are colors for each.
EXTERN float ambient[3] ;
EXTERN float diffuse[3] ;
EXTERN float specular[3] ;
EXTERN float emission[3] ;
EXTERN float shininess ;

// Vertex Variables
// Note: norms are commented out because norm commands are not used in tests...
const int numVertices = 10000;
EXTERN int maxverts ;
EXTERN vec3 vertices[numVertices] ;
EXTERN int verticesused;
//EXTERN int maxvertnorms ;
//EXTERN vec3 vertexNorms[numVertices] ;


// For multiple objects, read from a file.  
const int maxobjects = 10000 ;
EXTERN int numobjects ; 
EXTERN struct object {
  shape type ; 
  float size ;
  float ambient[3] ;
  float diffuse[3] ;
  float specular[3] ;
  float emission[3] ;
  int trianglevertices[3] ;
  float spherecenter[3] ;
  float shininess ;
  mat4 transform ; 
} objects[maxobjects] ;

// Variables to set uniform params for lighting fragment shader 
EXTERN uint lightcol ;
EXTERN uint lightpos ;
EXTERN uint numusedcol ;
EXTERN uint enablelighting ;
EXTERN uint ambientcol ;
EXTERN uint diffusecol ;
EXTERN uint specularcol ;
EXTERN uint emissioncol ;
EXTERN uint shininesscol ;

