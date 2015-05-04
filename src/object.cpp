/*
 * object.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: kenaco
 */

#include <glm/glm.hpp>
#include "object.hpp"
#include "log.hpp"


void Object::modelMatrix(glm::mat4 modelMatrix) {
	modelMatrix_ = modelMatrix;
	LOG_MATRIX(name_+".modelMatrix = ", modelMatrix_);
}


/*void Object::modelMatrix(glm::mat4& modelMatrix) {
	modelMatrix_ = modelMatrix;
	LOG_MATRIX(name_+".modelMatrix = ", modelMatrix_);
}*/


glm::mat4& Object::modelMatrix() {
	LOG_MATRIX(name_+".modelMatrix", modelMatrix_);
	return modelMatrix_;
}


glm::vec3 Object::position() {
	LOG(debug) << name_ << ".position[" << position_.x << ", " << position_.y << ", " << position_.z << "]";
	return position_;
}

glm::vec3 Object::world_position() {
	glm::vec3 ret = glm::vec3(modelMatrix_ * glm::vec4(position_, 1.f));
	LOG_VEC3(name_ +".world_position", ret);
	return ret;
}


Object::Object(): position_{0.f,0.f,0.f} {
	modelMatrix_ = glm::mat4(1.f);

}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

