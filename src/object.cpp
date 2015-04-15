/*
 * object.cpp
 *
 *  Created on: Apr 15, 2015
 *      Author: kenaco
 */

#include <glm/glm.hpp>
#include "object.hpp"

Object::Object(): position_{0.f,0.f,0.f} {
	modelMatrix_ = glm::mat4(1.f);

}

Object::~Object() {
	// TODO Auto-generated destructor stub
}

