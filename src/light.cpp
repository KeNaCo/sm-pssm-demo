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


DirectLight::DirectLight(): intensity_(1), diffuse_{0.5, 0.5, 0.5}, ambient_{0.2, 0.2, 0.2},
		specular_{0.5, 0.5, 0.5}, position_{6.9, 2.5, 5.0} {

	LOG(info) << "Light()";

	lookAt_ = glm::vec3(1.f) - position_; //TODO napevno!!
	up_ = glm::vec3(0.f,0.f,1.f); // Blender ma y ako hlbku

	LOG(info) << "Light() done";
}


DirectLight::~DirectLight() {}



glm::mat4 DirectLight::viewMatrix() {
	return glm::lookAt(position_, lookAt_, up_);
}


glm::mat4 DirectLight::projectionMatrix(float width, float height) {
	float rad = glm::radians(45.f);
	return glm::perspective(rad, width/height, 1.f, 10000.f); //TODO natvrdo!
}

glm::mat4 DirectLight::modelMatrix() {
	return glm::mat4(1.f);
}


glm::mat4 DirectLight::mvp(float width, float height) {
	return viewMatrix() * projectionMatrix(width, height) * modelMatrix();
}


void DirectLight::set(Shader* shader,  float width, float height) {
	glm::dmat4 modelViewM = viewMatrix() * modelMatrix();
	glm::dmat4 projectionM = projectionMatrix(width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixd(&projectionM[0][0]);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixd(&modelViewM[0][0]);
}
