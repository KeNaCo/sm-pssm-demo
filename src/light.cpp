/*
 * light.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: janporhincak
 */

#include <assimp/light.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "log.hpp"
#include "light.hpp"

using namespace gl;


Light::Light(): intensity_(60), color{1.f,1.f,1.f}, position{5.9, 2.5, 4.0} {
	LOG(info) << "Light()";
	LOG(debug) << "Light.position [" << position.x << ", " << position.y << ", " << position.z << "]";
	LOG(debug) << "Light.color [" << color.r << ", " << color.g << ", " << color.b << "]";
	LOG(debug) << "Light.intensity " << intensity_;
	LOG(info) << "Light() done";
}


Light::Light(aiLight* light) {
	// TODO
}


Light::~Light() {}


DirectLight::DirectLight(): Light() {

	LOG(info) << "DirectLight()";

	lookAt_ = glm::vec3(0.f,0.f,0.f) - position; //TODO napevno!!
	up_ = glm::vec3(0.f,0.f,1.f); // Blender ma y ako hlbku

	LOG(info) << "DirectLight() done";
}


DirectLight::~DirectLight() {}



glm::mat4 DirectLight::viewMatrix() {
	return glm::lookAt(position, lookAt_, up_);
}


glm::mat4 DirectLight::projectionMatrix(float width, float height) {

	return glm::ortho<float>(-10,10,-10,10,-10,20);
}

glm::mat4 DirectLight::modelMatrix() {
	return glm::mat4(1.f);
}


glm::mat4 DirectLight::mvp(float width, float height) {
	return projectionMatrix(width, height) * viewMatrix() * modelMatrix();
}
