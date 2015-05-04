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
using namespace std;


void Camera::init_viewMatrix() {
	viewMatrix_ = glm::lookAt(world_position(), world_lookAt(), world_up());
}


void Camera::init_projectionMatrix() {
	if (width_ != 0 && height_ != 0)
		projectionMatrix_= glm::perspective<float>(fov_, width_/height_, near_, far_);
}


void Camera::width(const float width) {
	width_ = width;
	init_projectionMatrix();
}

void Camera::height(const float height) {
	height_ = height;
	init_projectionMatrix();
}


void Camera::position(glm::vec3 position) {
	LOG_VEC3(name_+".position = ", position);
	position_ = position;
	init_viewMatrix();
}


void Camera::modelMatrix(glm::mat4 modelMatrix) {
	LOG_MATRIX(name_+".modelMatrix = ", modelMatrix);
	modelMatrix_ = modelMatrix;
	init_viewMatrix();
}


void Camera::lookAt(glm::vec3 lookAt) {
	lookAt_ = lookAt;
	init_viewMatrix();
}


void Camera::up(glm::vec3 up) {
	up_ = up;
	init_viewMatrix();
}


glm::vec3 Camera::world_lookAt() {
	glm::vec3 ret = glm::vec3(modelMatrix_ * glm::vec4(lookAt_, 0.f));
	LOG_VEC3(name_+".world_lookAt", ret);
	return ret;
}


glm::vec3 Camera::world_up() {
	glm::vec3 ret = glm::vec3(modelMatrix_ * glm::vec4(up_, 0.f));
	LOG_VEC3(name_+".world_lookAt", ret);
	return ret;
}


glm::mat4 Camera::mvp(glm::mat4 modelMatrix) {
	glm::mat4 mvp = projectionMatrix() * viewMatrix() * modelMatrix;
	LOG_MATRIX(name_ +".mvp", mvp);
	return mvp;
}


Camera::Camera(string name, float near, float far, float fov, glm::vec3 lookAt, glm::vec3 up):
		near_(near), far_(far), fov_(fov), lookAt_(lookAt), up_(up) {
	name_ = name;
	modelMatrix_ = glm::mat4(1.f);
	init_viewMatrix();
	init_projectionMatrix();
	LOG(info) << "Camera( " << name << " ) done";
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
	init_viewMatrix();
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
