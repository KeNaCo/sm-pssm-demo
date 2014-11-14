/*
 * util.h
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_UTIL_HPP_
#define SUBPROJECTS__SRC_UTIL_HPP_

#include <glm/glm.hpp>

glm::mat4 toMat4_cast(aiMatrix4x4& matrix) {
	return glm::mat4(matrix.a1, matrix.a2, matrix.a3, matrix.a4,
					 matrix.b1, matrix.b2, matrix.b3, matrix.b4,
					 matrix.c1, matrix.c2, matrix.c3, matrix.c4,
					 matrix.d1, matrix.d2, matrix.d3, matrix.d4);
}


glm::vec3 toVec3_cast(aiVector3D& vector) {
	return glm::vec3(vector.x, vector.y, vector.z);
}

#endif /* SUBPROJECTS__SRC_UTIL_HPP_ */
