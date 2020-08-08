// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

const mat3 identityMatrix = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);

float toRadians(float degrees) {
  return degrees * (piConst / 180);
}

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis)
{
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.
  float radians = toRadians(degrees);
  vec3 normAxis = normalize(axis);

  float x = axis.x;
  float y= axis.y;
  float z= axis.z;
  // You will change this return call
  return (cos(radians) * identityMatrix) + \
    (1 - cos(radians)) * mat3(pow(x, 2), x * y, x * z, x * y, pow(y, 2), y * z, x * z, y * z, pow(z, 2)) + \
    (sin(radians) * mat3(0, z, -y, -z, 0, x, y, -x, 0));
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  // vec3& is the pointer of the vec3, so will need to destructure
  // Note: the eye vector is the vector from origin to camera (e.g. the position of the camera)
  // What is my intuition on how to do this?
  // 1. establish a coordinate frame to get the axis of rotation for the left rotation
  //      [DOESN'T SEEM LIKE I NEED THIS STEP, Maybe?]
  // 2. create a rotation matrix, using the arbitrary axis rotation formula
  // 3. apply the rotation to the eye and up vectors?...
  mat3 rotationMatrix = Transform::rotate(degrees, up);

  eye = rotationMatrix * eye;
  // This is probably extraneous because it's rotating around this axis.
  up = rotationMatrix * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.
  // Intuition on how to do this?
  // 1. establish CF, and use orthogonal component to eye and up for rotation.
  // w = normalized eye using glm.normalize
  // u = up x w / || up x w || normalized orthogonal (pretty sure this is the one i want to use)
  // Compute the axis of rotation
  vec3 w = glm::normalize(eye);
  vec3 u = glm::cross(up, w);

  // Compute the rotation matrix
  mat3 rotationMatrix = Transform::rotate(-degrees, u);

  // Apply the rotation to eye and up
  eye = rotationMatrix * eye;
  up = rotationMatrix * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.
  // You will change this return call
  // How to do this?
  // 1. compute CF
  // 2. Apply translation
  vec3 w = glm::normalize(eye);
  vec3 u = glm::normalize(glm::cross(up, w));
  vec3 v = glm::cross(w, u);
  mat4 rotationMatrix = mat4(
    u.x, v.x, w.x, 0,
    u.y, v.y, w.y, 0,
    u.z, v.z, w.z, 0,
    0, 0, 0, 1
  );

  mat4 translationMatrix = mat4(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    -eye.x, -eye.y, -eye.z, 1
  );

  return rotationMatrix * translationMatrix;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  mat4 ret;
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.
  float a = -(zFar + zNear)/(zFar - zNear);
  float b = -(2 * zFar * zNear)/(zFar - zNear);
  float d = 1/tan(toRadians(fovy) / 2);

  return mat4(
    d/aspect, 0, 0, 0,
    0,        d, 0, 0,
    0,        0, a, -1,
    0,        0, b, 0
    );

  // for testing
//  return glm::perspective(fovy, aspect, zNear, zFar);
//  return glm::perspective(fovy, aspect, zNear, zFar);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 
  return mat4(
    sx, 0,  0,  0,
    0,  sy, 0,  0,
    0,  0,  sz, 0,
    0,  0,  0,  1
    );
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement translation
  return mat4(
    1,  0,  0,  0,
    0,  1,  0,  0,
    0,  0,  1,  0,
    tx, ty, tz, 1
    );
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
