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

class EventHandler {
public:
	virtual ~EventHandler() {};
	virtual void operator()(SDL_Event event, int deltaT, int v)=0;
};

class BaseHandler {
	//zakladne veci, vypinanie okna etc..
};

class CameraHandler: public EventHandler {
	Camera *camera;

	void move_forward(int deltaT, int v);
	void move_backward(int deltaT, int v);
public:
	CameraHandler(Camera *camera): camera(camera) {};
	virtual ~CameraHandler() {};

	virtual void operator()(SDL_Event event, int deltaT, int v);
};

#endif /* SUBPROJECTS__SRC_HANDLER_HPP_ */
