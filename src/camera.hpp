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

class Camera {
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
	float near;
	float far;
	float fov;

public:
	std::string name;

	Camera(aiCamera* camera);
	virtual ~Camera();
	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix(float width, float height);
};

#endif /* SUBPROJECTS__SRC_CAMERA_H_ */
