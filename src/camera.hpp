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

#include "shader.hpp"


class Camera {
	float near_;
	float far_;
	float fov_;

	glm::vec3 position_;
	glm::vec3 lookAt_;
	glm::vec3 up_;

	std::string name_;

public:
	glm::vec3 position() { return position_; }
	glm::vec3 lookAt() { return lookAt_; }
	glm::vec3 up() { return up_; }

	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix(float width, float height);
	glm::mat4 modelMatrix();
	glm::mat4 mvp(float width, float height);

	Camera(aiCamera* camera);
	Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up,
			float near, float far, float fov);
	virtual ~Camera();
};

#endif /* SUBPROJECTS__SRC_CAMERA_H_ */

