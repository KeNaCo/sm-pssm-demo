/*
 * handler.hpp
 *
 *  Created on: Nov 25, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_HANDLER_HPP_
#define SUBPROJECTS__SRC_HANDLER_HPP_

#include <SDL_events.h>
#include "camera.hpp"

class CameraHandler {

public:
	CameraHandler();
	~CameraHandler();

	void move_forward(int deltaT, float v, Camera* camera);
	void move_backward(int deltaT, float v, Camera* camera);
	void move_left(int deltaT, float v, Camera* camera);
	void move_right(int deltaT, float v, Camera* camera);
};

#endif /* SUBPROJECTS__SRC_HANDLER_HPP_ */
