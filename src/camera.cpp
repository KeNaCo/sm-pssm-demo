/*
 * camera.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/camera.h>
#include <string>

#include "log.hpp"
#include "camera.hpp"
#include "util.hpp"


/*
 * Initialize camera from assimp structure
 */
Camera::Camera(aiCamera* camera) {
	LOG(info) << "Camera::Camera()";

	modelMatrix_ = glm::mat4(1.0f);
	position = aiVector3D_to_Vec3_cast(camera->mPosition);
	LOG(debug) << "Camera.position [" << position.x << ", "
									  << position.y << ", "
									  << position.z << "]";

	lookAt = aiVector3D_to_Vec3_cast(camera->mLookAt);
	LOG(debug) << "Camera.lookAt [" << lookAt.x << ", "
									<< lookAt.y << ", "
									<< lookAt.z << "]";
	up = aiVector3D_to_Vec3_cast(camera->mUp);
	LOG(debug) << "Camera.up [" << up.x << ", "
								<< up.y << ", "
								<< up.z << "]";

	near = camera->mClipPlaneNear;
	far = camera->mClipPlaneFar;
	fov = camera->mHorizontalFOV;

	name = std::string(camera->mName.C_Str());

	LOG(info) << "Camera::Camera() done";
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


/*
 * Calculate view matrix
 */
glm::mat4 Camera::viewMatrix() {
	return glm::lookAt(position, lookAt, up);
}


glm::mat4 Camera::projectionMatrix(float width, float height) {
	return glm::perspective(fov, width/height, near, far);
}


glm::mat4 Camera::modelMatrix() {
	return modelMatrix_;
}


void Camera::translate(glm::vec3 vec) {
	modelMatrix_ = glm::translate(modelMatrix_, vec);
}


void Camera::rotate(float angle, glm::vec3 axis) {
	LOG(info) << "Camera::rotate()";
	translate(position);
	modelMatrix_ = glm::rotate(modelMatrix_, angle, axis);
	translate(-position);
	LOG(info) << "Camera::rotate() done";
}
