/*
 * camera.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#define GLM_FORCE_RADIANS

#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/camera.h>
#include <string>

#include "log.hpp"
#include "camera.hpp"
#include "util.hpp"

using namespace gl;


/*
 * Calculate view matrix
 */
glm::mat4 Camera::viewMatrix() {
	return glm::lookAt(position_, lookAt_, up_);
}


glm::mat4 Camera::projectionMatrix(float width, float height) {
	return glm::perspective(fov_, width/height, near_, far_);
//	return glm::ortho(-5.f, 5.f, -5.f, 5.f, near_, far_);
}


glm::mat4 Camera::mvp(float width, float height) {
	return projectionMatrix(width, height) * viewMatrix() * modelMatrix();
}

glm::mat4 Camera::mvp() {
	return projectionMatrix_ * viewMatrix_ * modelMatrix_;
}



Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up,
			   float near, float far, float fov):
		near_(near), far_(far), fov_(fov), lookAt_(lookAt), up_(up) {

	position_ = position;
	LOG(debug) << "Camera(): pos[" << position_.x << ", " << position_.y << ", " << position_.z << "] "
			  << "lookAt[" << lookAt_.x << ", " << lookAt_.y << ", " << lookAt_.z << "] "
			  << "up[" << up_.x << ", " << up_.y << ", " << up_.z << "] "
			  << "near " << near_ << " far " << far_ << " fov " << fov_;
}


Camera::Camera(DirectLight* light) {
	position_ = light->position();
	modelMatrix_ = light->modelMatrix();

	near_ = 0.1f;
	far_ = 100.f;
	fov_ = 45.f;

	lookAt_ = light->direction();
	up_ = glm::vec3(0.f, 0.f, 1.f); // TODO podla Blenderu

	viewMatrix_ = glm::lookAt(position_, lookAt_, glm::vec3(0.f,1.f,0.f));
	projectionMatrix_ = light->projectionMatrix();

	LOG(debug) << "Camera(DirectLight*): pos[" << position_.x << ", " << position_.y << ", " << position_.z << "] "
				  << "lookAt[" << lookAt_.x << ", " << lookAt_.y << ", " << lookAt_.z << "] "
				  << "up[" << up_.x << ", " << up_.y << ", " << up_.z << "] "
				  << "near " << near_ << " far " << far_ << " fov " << fov_;
}


/*
 * Initialize camera from assimp structure
 */
Camera::Camera(aiCamera* camera) {
	position_ = aiVector3D_to_Vec3_cast(camera->mPosition);
	lookAt_ = aiVector3D_to_Vec3_cast(camera->mLookAt);
	up_ = aiVector3D_to_Vec3_cast(camera->mUp);

	near_ = camera->mClipPlaneNear;
	far_ = camera->mClipPlaneFar;
	fov_ = camera->mHorizontalFOV;

	LOG(info) << "Camera(aiCamera): pos[" << position_.x << ", " << position_.y << ", " << position_.z << "] "
			  << "lookAt[" << lookAt_.x << ", " << lookAt_.y << ", " << lookAt_.z << "] "
			  << "up[" << up_.x << ", " << up_.y << ", " << up_.z << "] "
			  << "near " << near_ << " far " << far_ << " fov " << fov_;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}
