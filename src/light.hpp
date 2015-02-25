/*
 * light.hpp
 *
 *  Created on: Feb 25, 2015
 *      Author: janporhincak
 */

#ifndef SUBPROJECTS__SRC_LIGHT_HPP_
#define SUBPROJECTS__SRC_LIGHT_HPP_

#include <assimp/light.h>
#include <glm/glm.hpp>
#include <string>

class ShadowInfo {

};

class Light {
	float intensity;
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;

public:
	glm::vec3 position;

	std::string name;

	//TODO rozsirit o shadery?

	Light(const aiLight* light);
	virtual ~Light();
};

#endif /* SUBPROJECTS__SRC_LIGHT_HPP_ */
