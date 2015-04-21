/*
 * camera.h
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_CAMERA_H_
#define SUBPROJECTS__SRC_CAMERA_H_

#include <assimp/camera.h>
#include <glm/glm.hpp>
#include <string>

#include "object.hpp"
#include "light.hpp"


class Camera: public Object {
	float near_;
	float far_;
	float fov_;

	glm::vec3 lookAt_;
	glm::vec3 up_;

	glm::mat4 viewMatrix_;
	glm::mat4 projectionMatrix_;

public:
	void lookAt(glm::vec3 lookAt) { lookAt_ = lookAt; }
	glm::vec3 world_lookAt();

	glm::mat4 viewMatrix();
	void projectionMatrix(float width, float height);
	glm::mat4 projectionMatrix();
	glm::mat4 mvp(glm::mat4 modelMatrix);

	Camera() {}
	Camera(DirectLight* light);
	Camera(aiCamera* camera);
	virtual ~Camera();
};

#endif /* SUBPROJECTS__SRC_CAMERA_H_ */

