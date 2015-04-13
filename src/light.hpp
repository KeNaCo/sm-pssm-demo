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

#include "shader.hpp"


class Light {
public:
	float intensity_;
	glm::vec3 color;

	glm::vec3 position;

	Light();
	Light(aiLight* light);
	~Light();
};


class DirectLight: public Light {
	glm::vec3 lookAt_;
	glm::vec3 up_;

public:
	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix(float width, float height);
	glm::mat4 modelMatrix();
	glm::mat4 mvp(float width, float height);

	DirectLight();
	virtual ~DirectLight();
};

#endif /* SUBPROJECTS__SRC_LIGHT_HPP_ */
