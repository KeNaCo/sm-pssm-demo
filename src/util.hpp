/*
 * util.h
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_UTIL_HPP_
#define SUBPROJECTS__SRC_UTIL_HPP_

#include <glm/glm.hpp>

#include "log.hpp"

inline glm::mat4 aiMatrix4x4ToMat4_cast(aiMatrix4x4& matrix) {
	return glm::mat4(matrix.a1, matrix.a2, matrix.a3, matrix.a4,
					 matrix.b1, matrix.b2, matrix.b3, matrix.b4,
					 matrix.c1, matrix.c2, matrix.c3, matrix.c4,
					 matrix.d1, matrix.d2, matrix.d3, matrix.d4);
}


inline glm::vec3 aiVector3D_to_Vec3_cast(aiVector3D& vector) {
	return glm::vec3(vector.x, vector.y, vector.z);
}


inline glm::vec4 aiColor4D_to_Vec4_cast(aiColor4D& color) {
	return glm::vec4(color.r, color.g, color.b, color.a);
}

inline void aiColor3D_to_float_cast(float* color, const aiColor3D& aiColor) {
	color[0] = aiColor.r;
	color[1] = aiColor.g;
	color[2] = aiColor.b;
}

#endif /* SUBPROJECTS__SRC_UTIL_HPP_ */
