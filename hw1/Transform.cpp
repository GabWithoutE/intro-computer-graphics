// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <stdio.h>

const mat3 identityMatrix = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);

float toRadians(float degrees) {
    return degrees * (M_PI / 180.0f);
}

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	float radians = toRadians(degrees);
	float x = axis.x;
    float y= axis.y;
    float z= axis.z;
	// You will change this return call
	return (cos(radians) * identityMatrix) + \
	    (1 - cos(radians)) * mat3(pow(x, 2), x * y, x * z, x * y, pow(y, 2), y * z, x * z, y * z, pow(z, 2)) + \
        (sin(radians) * mat3(0, z, -y, -z, 0, x, y, -x, 0));
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	// vec3& is the pointer of the vec3, so will need to destructure
	// Note: the eye vector is the vector from origin to camera (e.g. the position of the camera)
	// What is my intuition on how to do this?
	// 1. establish a coordinate frame to get the axis of rotation for the left rotation
	//      [DOESN'T SEEM LIKE I NEED THIS STEP, Maybe?]
	// 2. create a rotation matrix, using the arbitrary axis rotation formula
	// 3. apply the rotation to the eye and up vectors?...
    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
    mat3 rotationMatrix = Transform::rotate(degrees, up);

    eye = rotationMatrix * eye;
    // This is probably extraneous because it's rotating around this axis.
    up = rotationMatrix * up;
    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
	// Intuition on how to do this?
	// 1. establish CF, and use orthogonal component to eye and up for rotation.
	// w = normalized eye using glm.normalize
	// u = up x w / || up x w || normalized orthogonal (pretty sure this is the one i want to use)
    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
    // Compute the axis of rotation
    vec3 w = glm::normalize(eye);
    vec3 u = glm::cross(up, w);

    // Compute the rotation matrix
    mat3 rotationMatrix = Transform::rotate(-degrees, u);

    // Apply the rotation to eye and up
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE

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

Transform::Transform()
{

}

Transform::~Transform()
{

}
