/*
 * renderer.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: kenaco
 */


#include <SDL.h>
#include <SDL_video.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include "log.h"
#include "renderer.h"


using namespace gl;


Renderer_t::Renderer_t(SDL_Window* window) {
	LOG(info) << "Renderer_t constructor";

	gl = SDL_GL_CreateContext(window);

	glbinding::Binding::initialize();

	glOrtho(0.0, 4.0, 0.0, 3.0, -1.0, 1.0);

	LOG(info) << "Renderer_t constructor done";
}

Renderer_t::~Renderer_t() {
	LOG(info) << "Renderer_t destructor";

	SDL_GL_DeleteContext(gl);

	LOG(info) << "Renderer_t destructor done";
}


void Renderer_t::render() {
	LOG(info) << "Renderer_t.render()";
//	glBegin(GL_TRIANGLES);
/*
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7, 0.5, 0.8);
	glRectf(1.0, 1.0, 3.0, 2.0);
*/
//	glEnd();

	glClearColor (0.0, 0.0, 0.0, 0.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f (0.25, 0.25, 0.0);
	    glVertex3f (0.75, 0.25, 0.0);
	    glVertex3f (0.75, 0.75, 0.0);
	    glVertex3f (0.25, 0.75, 0.0);
	glEnd();
	glFlush();

	LOG(info) << "Renderer_t.render() done";
}
