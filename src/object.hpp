/*
 * object.hpp
 *
 *  Created on: Apr 15, 2015
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_OBJECT_HPP_
#define SUBPROJECTS__SRC_OBJECT_HPP_

#include <glm/glm.hpp>

class Object {
protected:
	glm::vec3 position_;
	glm::mat4 modelMatrix_;
public:
	void position(glm::vec3 position) { position_ = position; }
	glm::vec3 position() { return position_; }
	glm::vec3 world_position() { return glm::vec3(modelMatrix_ * glm::vec4(position_, 1.f)); }

	Object();
	virtual ~Object();
};

#endif /* SUBPROJECTS__SRC_OBJECT_HPP_ */
