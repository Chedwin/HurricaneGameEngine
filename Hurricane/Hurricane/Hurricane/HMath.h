//*******************************//
//
// Name:			HMath.h
// Description:		A simple header that includes all the necessary GLM header files.
//					All credit goes to Silicon Graphics Inc.
//
// Author:			Edwin Chen
// Created:			Oct 08, 2016
// Last updated:	Nov 19, 2016
//
//*******************************//


#ifndef HMATH_H
#define HMATH_H

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>

// LET'S MACRO DEFINE SOME GLM TERMS

// Vector2
#define VEC2 glm::vec2

// Vector3
#define VEC3 glm::vec3
#define ORIGIN glm::vec3(0.0f, 0.0f, 0.0f)
#define BASIS3X glm::vec3(1.0f, 0.0f, 0.0f)
#define BASIS3Y glm::vec3(0.0f, 1.0f, 0.0f)
#define BASIS3Z glm::vec3(1.0f, 0.0f, 1.0f)

// Vector4
#define VEC4 glm::vec4

// Matrices
#define MATRIX3 glm::mat3
#define MATRIX4 glm::mat4
#define MAT_IDENTITY4 glm::mat4(1.0f)

// Quaternions
#define QUATERNION glm::quat

#endif