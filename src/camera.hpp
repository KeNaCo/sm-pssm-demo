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

	float width_;
	float height_;

	glm::vec3 lookAt_;
	glm::vec3 up_;

	glm::mat4 viewMatrix_;
	glm::mat4 projectionMatrix_;

	void init_viewMatrix();
	void init_projectionMatrix();
public:
	void width(const float width);
	void height(const float height);

	void position(glm::vec3 position);

	void modelMatrix(glm::mat4 modelMatrix);

	void lookAt(glm::vec3 lookAt);
	glm::vec3 lookAt() { return lookAt_; }
	glm::vec3 world_lookAt();

	void up(glm::vec3 up);
	glm::vec3 up() { return up_; }
	glm::vec3 world_up();

	void viewMatrix(glm::mat4 viewMatrix) { viewMatrix_ = viewMatrix; }
	glm::mat4 viewMatrix() { return viewMatrix_; }

	void projectionMatrix(glm::mat4 projectionMatrix) { projectionMatrix_ = projectionMatrix; }
	glm::mat4 projectionMatrix() { return projectionMatrix_; }

	glm::mat4 mvp(glm::mat4 modelMatrix);

	Camera() {}
	Camera(string name, float near, float far, float fov, glm::vec3 lookAt, glm::vec3 up);
	Camera(DirectLight* light);
	Camera(aiCamera* camera);
	virtual ~Camera();
};

#endif /* SUBPROJECTS__SRC_CAMERA_H_ */

