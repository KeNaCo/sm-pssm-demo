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
}


glm::mat4 Camera::modelMatrix() {
	return glm::mat4(1.0f);
}

glm::mat4 Camera::mvp(float width, float height) {
	return viewMatrix() * projectionMatrix(width, height) * modelMatrix();
}


void Camera::set(Shader* shader,  float width, float height) {
	glm::dmat4 modelViewM = viewMatrix() * modelMatrix();
	glm::dmat4 projectionM = projectionMatrix(width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMultMatrixd(&projectionM[0][0]);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glMultMatrixd(&modelViewM[0][0]);
}
