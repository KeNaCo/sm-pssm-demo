/*
 * handler.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: kenaco
 */

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "log.hpp"
#include "handler.hpp"
#include "camera.hpp"

/**
 * Fcia vyrata novu poziciu kamery pri pohybe dopredu v case deltaT
 *
 * @param deltaT: casove kvantum pohybu [msek]
 * @param v: rychlost pohybu [m/s]
 */
void CameraHandler::move_forward(int deltaT, float v, Camera* camera) {
	float vSize = deltaT * v /100.0f;
	glm::vec3 vector = (-vSize) * glm::normalize(camera->lookAt);
	camera->translate(vector);
	LOG(debug) << "vector[" << vector.x << ", "
							<< vector.y << ", "
							<< vector.z << "]";
}


void CameraHandler::move_backward(int deltaT, float v, Camera* camera) {
	float vSize = deltaT * v / 100.0f;
	glm::vec3 vector = vSize * glm::normalize(camera->lookAt);
	camera->translate(vector);
	LOG(debug) << "vector[" << vector.x << ", "
							<< vector.y << ", "
							<< vector.z << "]";
}


void CameraHandler::move_left(int deltaT, float v, Camera* camera) {
	float vSize = deltaT * v / 100.0f;
	glm::vec3 left = glm::cross(camera->lookAt, camera->up);
	glm::vec3 vector = vSize * glm::normalize(left);
	camera->translate(vector);
}


void CameraHandler::move_right(int deltaT, float v, Camera* camera) {
	float vSize = deltaT * v / 100.0f;
	glm::vec3 left = glm::cross(camera->lookAt, camera->up);
	glm::vec3 vector = (-vSize) * glm::normalize(left);
	camera->translate(vector);
}
CameraHandler::CameraHandler() {}
CameraHandler::~CameraHandler() {}
