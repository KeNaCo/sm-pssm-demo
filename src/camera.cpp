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


glm::vec3 Camera::world_lookAt() {
	glm::vec3 ret = glm::vec3(glm::vec4(lookAt_, 0.f) * modelMatrix_);
	LOG_VEC3(name_+".world_lookAt", ret);
	return ret;
}


/*
 * Calculate view matrix
 */
glm::mat4 Camera::viewMatrix() {
	glm::mat4 ret = glm::lookAt(world_position(), world_lookAt(), up_);
	LOG_MATRIX(name_+".viewMatrix", ret);
	return ret;
}


void Camera::projectionMatrix(float width, float height) {
	projectionMatrix_ = glm::perspective(fov_, width/height, near_, far_);
}

glm::mat4 Camera::projectionMatrix() {
	LOG_MATRIX(name_+".projectionMatrix", projectionMatrix_);
	return projectionMatrix_;
}


glm::mat4 Camera::mvp(glm::mat4 modelMatrix) {
	glm::mat4 mvp = projectionMatrix() * viewMatrix() * modelMatrix;
	LOG_MATRIX(name_ +".mvp", mvp);
	return mvp;
}


Camera::Camera(DirectLight* light) {
	LOG(info) << "Camera(DirectLight)";
	name_ = light->name();
	position_ = light->position();
	modelMatrix_ = light->modelMatrix();

	near_ = 0.1f;
	far_ = 100.f;
	fov_ = 45.f;

	lookAt_ = light->direction();
	up_ = glm::vec3(0.f, 1.f, 0.f);
	viewMatrix_ = glm::lookAt(world_position(), lookAt_, up_);
	projectionMatrix_ = light->projectionMatrix();

	LOG_VEC3(name_+".position", position_);
	LOG_VEC3(name_+".lookAt", lookAt_);
	LOG_VEC3(name_+".up", up_);
	LOG(info) << "Camera(DirectLight) done";
}


/*
 * Initialize camera from assimp structure
 */
Camera::Camera(aiCamera* camera) {
	LOG(info) << "Camera.Camera(aiCamera)";
	position_ = aiVector3D_to_Vec3_cast(camera->mPosition);
	name_ = std::string(camera->mName.C_Str());
	lookAt_ = aiVector3D_to_Vec3_cast(camera->mLookAt);
	up_ = aiVector3D_to_Vec3_cast(camera->mUp);

	near_ = camera->mClipPlaneNear;
	far_ = camera->mClipPlaneFar;
	fov_ = camera->mHorizontalFOV;

	LOG_VEC3(name_+".position", position_);
	LOG_VEC3(name_+".lookAt", lookAt_);
	LOG_VEC3(name_+".up", up_);
	LOG(info) << "Camera.Camera(aiCamera) done";
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}
