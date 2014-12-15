/*
 * handler.cpp
 *
 *  Created on: Dec 14, 2014
 *      Author: kenaco
 */

#include <glm/glm.hpp>

#include "log.hpp"
#include "handler.hpp"

/**
 * Fcia vyrata novu poziciu kamery pri pohybe dopredu v case deltaT
 *
 * @param deltaT: casove kvantum pohybu [msek]
 * @param v: rychlost pohybu [m/s]
 */
void CameraHandler::move_forward(int deltaT, int v) {
	camera->position += glm::normalize(camera->lookAt) * (deltaT / 1000 * v);
	LOG(debug) << "Camera.position[" << camera->position.x << ", "
									 << camera->position.y << ", "
									 << camera->position.z << "]";
}


void CameraHandler::move_backward(int deltaT, int v) {
	camera->position -= glm::normalize(camera->lookAt) * (deltaT / 1000 * v);
	LOG(debug) << "Camera.position[" << camera->position.x << ", "
									 << camera->position.y << ", "
									 << camera->position.z << "]";
}


virtual void CameraHandler::operator()(SDL_Event event, int deltaT, int v) {
	switch(event.type) {
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym) {
		case SDLK_a:
			move_forward(deltaT, v);
			break;
		case SDLK_d:
			move_backward(deltaT, v);
			break;
		case SDLK_w:
//				camera->moveForward();
			break;
		case SDLK_s:
//				camera->moveY(false);
			break;
		default:
			break;
		}
		break;
	}
}
