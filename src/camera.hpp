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
	float near;
	float far;
	float fov;

	glm::mat4 modelMatrix_;

public:
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;

	std::string name;

	Camera(aiCamera* camera);
	virtual ~Camera();
	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix(float width, float height);
	glm::mat4 modelMatrix();

	void translate(glm::vec3 vec);
	void rotate(float angle, glm::vec3 axis);
};

#endif /* SUBPROJECTS__SRC_CAMERA_H_ */

