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
	glm::mat4 modelMatrix() { return modelMatrix_; }
	void lookAt(glm::vec3 lookAt) { lookAt_ = lookAt; }

	glm::mat4 viewMatrix();
	glm::mat4 projectionMatrix(float width, float height);
	glm::mat4 mvp();
	glm::mat4 mvp(float width, float height);

	// Up, lookAt setup for Blender axis orientation
	Camera(glm::vec3 position={0.f,0.f,0.f}, glm::vec3 lookAt={0.f,1.f,0.f},
			glm::vec3 up={0.f,0.f,1.f}, float near=0.1f, float far=100.f, float fov=45.f);
	Camera(DirectLight* light);
	Camera(aiCamera* camera);
	virtual ~Camera();
};

#endif /* SUBPROJECTS__SRC_CAMERA_H_ */

