/*
 * log.h
 *
 *  Created on: Oct 15, 2014
 *      Author: kenaco
 */

#ifndef LOG_H_
#define LOG_H_

#include <boost/log/trivial.hpp>
#include <glm/glm.hpp>
#include <string>

#define LOG(severity) BOOST_LOG_TRIVIAL(severity)

/** Examples
 *
 * LOG(trace) << "A trace severity message";
 * LOG(debug) << "A debug severity message";
 * LOG(info) << "An informational severity message";
 * LOG(warning) << "A warning severity message";
 * LOG(error) << "An error severity message";
 * LOG(fatal) << "A fatal severity message";
 */

inline void LOG_MATRIX(std::string text, glm::mat4& m) {
	LOG(debug) << text << std::endl << "{"
			<< "{" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << ", " << "}" << std::endl
			<< "{" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << ", " << "}" << std::endl
			<< "{" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << ", " << "}" << std::endl
			<< "{" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "}" << "}";
}


inline void LOG_VEC3(std::string text, glm::vec3& v) {
	LOG(debug) << text << std::endl << "{" << v.x << ", " << v.y << ", " << v.z << "}";
}

#endif /* LOG_H_ */
