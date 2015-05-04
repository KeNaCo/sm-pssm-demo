/*
 * object.hpp
 *
 *  Created on: Apr 15, 2015
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_OBJECT_HPP_
#define SUBPROJECTS__SRC_OBJECT_HPP_

#include <glm/glm.hpp>
#include <string>


class Object {
protected:
	glm::vec3 position_;
	glm::mat4 modelMatrix_;

	std::string name_;
public:
	void position(glm::vec3 position) { position_ = position; }
	glm::vec3 position();
	glm::vec3 world_position();

	void modelMatrix(glm::mat4 modelMatrix);
//	void modelMatrix(glm::mat4& modelMatrix);
	glm::mat4& modelMatrix();

	std::string name() { return name_; }

	Object();
	virtual ~Object();
};

#endif /* SUBPROJECTS__SRC_OBJECT_HPP_ */
