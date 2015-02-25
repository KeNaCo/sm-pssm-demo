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

class ShadowInfo {

};

class Light {
	float intensity;
	float diffuse[3];
	float ambient[3];
	float specular[3];

	//TODO rozsirit o shadery?

public:

	Light(const aiLight* light);
	virtual ~Light();
};

#endif /* SUBPROJECTS__SRC_LIGHT_HPP_ */
