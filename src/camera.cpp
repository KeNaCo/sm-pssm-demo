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
 * Initialize camera from assimp structure
 */
Camera::Camera(aiCamera* camera) {
	LOG(info) << "Camera::Camera()";

	position_ = aiVector3D_to_Vec3_cast(camera->mPosition);
	LOG(debug) << "Camera.position [" << position_.x << ", "
									  << position_.y << ", "
									  << position_.z << "]";

	lookAt_ = aiVector3D_to_Vec3_cast(camera->mLookAt);
	LOG(debug) << "Camera.lookAt [" << lookAt_.x << ", "
									<< lookAt_.y << ", "
									<< lookAt_.z << "]";
	up_ = aiVector3D_to_Vec3_cast(camera->mUp);
	LOG(debug) << "Camera.up [" << up_.x << ", "
								<< up_.y << ", "
								<< up_.z << "]";

	near_ = camera->mClipPlaneNear;
	far_ = camera->mClipPlaneFar;
	fov_ = camera->mHorizontalFOV;

	name_ = std::string(camera->mName.C_Str());

	LOG(info) << "Camera::Camera() done";
}


Camera::Camera(glm::vec3 position, glm::vec3 lookAt, glm::vec3 up,
			   float near, float far, float fov):
		near_(near), far_(far), fov_(fov),
		position_(position), lookAt_(lookAt), up_(up) {

	LOG(info) << "Camera::Camera()";

	LOG(debug) << "Camera.position [" << position_.x << ", "
									  << position_.y << ", "
									  << position_.z << "]";

	LOG(debug) << "Camera.lookAt [" << lookAt_.x << ", "
									<< lookAt_.y << ", "
									<< lookAt_.z << "]";
	LOG(debug) << "Camera.up [" << up_.x << ", "
								<< up_.y << ", "
								<< up_.z << "]";

	name_ = std::string("customCamera");

	LOG(info) << "Camera::Camera() done";
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}


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


glm::mat4 Camera::modelMatrix() {
	return glm::mat4(1.0f);
}

glm::mat4 Camera::mvp(float width, float height) {
	return projectionMatrix(width, height) * viewMatrix() * modelMatrix();
}
