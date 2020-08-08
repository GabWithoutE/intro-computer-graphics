//
// Created by Gabriel Chen on 8/6/20.
//

#include "Raytracer.h"
#include "variables.h"
#include "Camera.h"
#include <iostream>

struct intersection {
  int objectindex;
  float intersectdepth;
  vec3 normal;
  vec3 pintersection;
};

bool atRightHandSideCrossProduct(vec3 first, vec3 second, vec3 normal) {
//  printf("positive?: %f\n", dot(cross(first, second), normal));
  return dot(cross(second, first), normal) > 0;
}

bool insideTriangle(vec3 point, vec3 a, vec3 b, vec3 c, vec3 normal) {
  // Computation description...
  //    Using the properties of cross product, we know that if P - A is inside the triangle, it's cross product with
  //    B - A (cp will be called X) will be in the same direction as the normal (N). Therefore X dot N will be positive.
  //    X dot N being negative means that P - A is on the left side of B - A, meaning it's outside of the triangle...
  //    Repeat this for each side to ensure that P - B, P - C are all within the triangle.
  // Steps...
  //    1. compute the dot products
  //    2. check the positive conditions

  return (
    atRightHandSideCrossProduct(point - a, b - a, normal) &&
    atRightHandSideCrossProduct(point - b, c - b, normal) &&
    atRightHandSideCrossProduct(point - c, a - c, normal)
  );
//  float beta = dot(point - a, b - a) / length(b - a);
//
//  if (beta > 1 && beta < 0) {
//    return false;
//  }
//
//  float gamma = dot(point - a, c - a) / length(c - a);
//
//  if (gamma > 1 && gamma < 0) {
//    return false;
//  }
//
//  return beta + gamma <= 1;
}

// Helper Functions
void intersectTriangle(object * triangle, Ray ray, bool &intersecting, intersection &info) {
  int * triangleverts = triangle->trianglevertices;

  mat4 transf = triangle->transform;
  vec3 a = vec3(transf * vec4(vertices[triangleverts[0]], 1));
  vec3 b = vec3(transf * vec4(vertices[triangleverts[1]], 1));
  vec3 c = vec3(transf * vec4(vertices[triangleverts[2]], 1));
//  vec3 a = vec3(vertices[triangleverts[0]]);
//  vec3 b = vec3(vertices[triangleverts[1]]);
//  vec3 c = vec3(vertices[triangleverts[2]]);

  vec3 normal = normalize(cross(b - a, c - a));

  float p1dotnorm = dot(ray.p1, normal);
  // if p1 dot norm, it means that the ray is parallel to the plane, and therefore does not intersect the plane
  if (p1dotnorm == 0) {
    intersecting = false;
    return;
  }

  float t = (dot(a, normal) - dot(ray.p0, normal)) / p1dotnorm; // distance of ray, for point that intersects plane
  vec3 planeintersect = ray.p0 + (t * ray.p1); // point of intersection between ray and plane

  // TODO: this is a hacky workaround for numerical issues when casting ray from an intersection (shadows)
  //    functions similarly to moving vertex towards the light, except seems to work better in this case.
  if (t < 0.001){
    intersecting = false;
    return;
  }

  if (insideTriangle(planeintersect, a, b, c, normal)) {
//    printf("a -- x: %f, y: %f, z: %f\n", a.x, a.y, a.z);
//    printf("b -- x: %f, y: %f, z: %f\n", b.x, b.y, b.z);
//    printf("c -- x: %f, y: %f, z: %f\n", c.x, c.y, c.z);
//    printf("plane: %f, %f, %f\n", planeintersect.x, planeintersect.y, planeintersect.z);

    intersecting = true;
    info.normal = normal;
    info.intersectdepth = t;
    info.pintersection = planeintersect;
    return;
  }

  intersecting = false;
}

void clearintersectioninfo(intersection &info, int currentindex) {
  info.objectindex = currentindex;
  info.intersectdepth = std::numeric_limits<float>::max();
}


intersection intersectObjects(Ray ray) {

  intersection nearestintersectionobject;

  nearestintersectionobject.intersectdepth = std::numeric_limits<float>::max();
  nearestintersectionobject.objectindex = -1;
  intersection currentinfo;

  for (int i = 0; i < numobjects; i++) {
    object *obj = &(objects[i]);
    if (obj->type == triangle) {
      clearintersectioninfo(currentinfo, i);

      bool * intersecting;
      intersectTriangle(obj, ray, *intersecting, currentinfo);

      if (!(*intersecting)) {
        continue;
      }

      if (currentinfo.intersectdepth < nearestintersectionobject.intersectdepth) {
        nearestintersectionobject = currentinfo;
      }
    }
  }
  return nearestintersectionobject;
}


vec3 computeColorFromUnobstructedLight(
  vec3 lightcolor,
  vec3 direction,
  vec3 normal,
  vec3 diffusion,
  vec3 halfvec,
  vec3 specular,
  float shininess
  ) {
  float nDotL = dot(normal, direction); // diffusion intensity
  vec3 lambert = diffusion * lightcolor * max(nDotL, 0.0f);

  float nDotH = dot(normal, halfvec); // specular intensity
  vec3 phong = specular * lightcolor * pow(max(nDotH, 0.0f), shininess) ;

  return lambert + phong;
}

// Note may need to handle edge case of point being ON an edge of the triangle. in this case, just check that the normalized
//    point to line normalized is equal to the edge normalized.

vec3 findColor(intersection inter) {
  vec3 totalcolor = vec3(0, 0, 0);

  // Laying out the different material properties
  object * obj = &(objects[inter.objectindex]);
  vec3 diffuse = vec3(obj->diffuse[0], obj->diffuse[1], obj->diffuse[2]);
  vec3 specular = vec3(obj->specular[0], obj->specular[1], obj->specular[2]);
  vec3 emission = vec3(obj->emission[0], obj->emission[1], obj->emission[2]);
  vec3 ambient = vec3(obj->ambient[0], obj->ambient[1], obj->ambient[2]);
  float shininess = obj->shininess;

  // Add the ambient and the emission terms...
  totalcolor += ambient + emission;

  // NOTE this will cause a seg fault...
  for (int i = 0; i < lightsused; i++ ){
    // color from the light's properties
    vec3 lightcol = vec3(lightcolor[3 * i], lightcolor[(3 * i) + 1], lightcolor[(3 * i) + 2]);

    if (lighttype[i] == point) {
      vec3 vertex = inter.pintersection;
      // location of the point light
      vec3 lightloc = vec3(lightposn[3 * i], lightposn[(3 * i) + 1], lightposn[(3 * i) + 2]);
      // vector from point to the light
      vec3 lightdir = normalize(lightloc - vertex);
      // convert to a ray for finding intersection
      Ray pointToLightRay = Ray(0, 0, lightdir, vertex); // move towards light before shooting to prevent numerical errors

      intersection shadowobstruction = intersectObjects(pointToLightRay);

      // if the light is obstructed (ray intersects some object) then we can ignore the effect of the light
      if (shadowobstruction.objectindex != -1) {
        continue;
      }

      // halfvector
      vec3 halfvec = normalize(lightdir + normalize(eye - inter.pintersection));

      vec3 pointlightvalue = computeColorFromUnobstructedLight(
        lightcol,
        lightdir,
        inter.normal,
        diffuse,
        halfvec,
        specular,
        shininess
      );

      totalcolor += pointlightvalue;
    }
    else if (lighttype[i] == directional) {
      // the light direction for direction lights is stored in the light position
      vec3 lightdir = normalize(vec3(lightposn[3 * i], lightposn[(3 * i) + 1], lightposn[(3 * i) + 2]));
      vec3 halfvec = normalize(lightdir + normalize(eye - inter.pintersection));

      vec3 directionallightvalue = computeColorFromUnobstructedLight(
        lightcol,
        lightdir,
        inter.normal,
        diffuse,
        halfvec,
        specular,
        shininess
      );

      totalcolor += directionallightvalue;
    }
  }

  // I = A + E + Sum V
  // steps...
  //    1. cast a shadow ray per light to see if there is an obstruction between each light and

  return totalcolor;
}

vec3 Raytracer::traceRay(Ray ray, int &currentdepth) {
  currentdepth++;
  intersection nearestinter = intersectObjects(ray);

  if (nearestinter.objectindex != -1){
    return findColor(nearestinter);
  }

  return vec3(0, 0, 0);
}
