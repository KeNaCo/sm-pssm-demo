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

#include "object.hpp"
#include "shader.hpp"


class Light: public Object {
protected:
	float intensity_;
	glm::vec3 color_;
	glm::mat4 projectionMatrix_;
public:

	float intensity() { return intensity_; }
	glm::vec3 color() { return color_; }
	glm::mat4 projectionMatrix() { return projectionMatrix_; }

	Light();
	~Light();
};


class DirectLight: public Light {
protected:
	glm::vec3 direction_;

public:
	glm::mat4 modelMatrix() { return modelMatrix_; }
	glm::vec3 direction() { return direction_; }

	DirectLight();
	DirectLight(aiLight* light);
	virtual ~DirectLight();
};

#endif /* SUBPROJECTS__SRC_LIGHT_HPP_ */
