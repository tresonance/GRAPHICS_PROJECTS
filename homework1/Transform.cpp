// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <stdio.h>
//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE
	mat3 second_matrix;
	mat3 third_matrix;
	mat3 result;
	vec3 axis_;

	axis_ = glm::normalize(axis);
	second_matrix = glm::mat3(
		axis_.x * axis_.x, axis_.x*axis_.y, axis_.x*axis_.z,
		axis_.y * axis_.x, axis_.y*axis_.y, axis_.y*axis_.z,
		axis_.z * axis_.x, axis_.z*axis_.y, axis_.z*axis_.z
	);

	third_matrix = glm::mat3(
		0.0f, -axis_.z, axis_.y,
		axis_.z, 0.0f, -axis_.x,
		-axis_.y, axis_.x, 0.0f
	);
	// You will change this return call
	//return mat3();
	result = glm::mat3(1.0f) * glm::cos(glm::radians(degrees)) + second_matrix * (1.0f - glm::cos(glm::radians(degrees))) + third_matrix * glm::sin(glm::radians(degrees));
	return result;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	mat3 m;
	// YOUR CODE FOR HW1 HERE
	m = Transform::rotate(degrees,up);
	eye =  eye * m;
	up = up * m;
	 printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 
	mat3 m;

	m = Transform::rotate(degrees, glm::normalize(glm::cross(eye,up)));
	eye = eye * m;
	up = up * m;
	 printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE
	mat4 matrix1;
	mat4 matrix2;
	mat4 result;
	vec3 w, u, v;

	matrix1 = mat4(
			1.0,    0.0,    0.0,   0.0f,
			0.0,    1.0,    0.0,   0.0f,
			0.0,    0.0,    1.0,   0.0f,
			-eye.x, -eye.y, -eye.z,1.0f
			);
	w = glm::normalize(eye);
	u = glm::normalize(glm::cross(up, w));
	v = glm::cross(w, u);

	matrix2 = mat4(
	u.x,   v.x,   w.x,  0.0f,
	u.y,   v.y,   w.y,  0.0f,
	u.z,   v.z,   w.z,  0.0f,
	0.0f,  0.0f,  0.0f, 1.0f
	);

	// You will change this return call
	//return mat4();
	result = matrix2 * matrix1;
	return result;
}

Transform::Transform()
{

}

Transform::~Transform()
{

}
