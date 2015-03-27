/*
 * texture.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Jan Porhinčák (xporhi00)
 */

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>

#include "log.hpp"
#include "texture.hpp"
#include "exceptions.hpp"

using namespace gl;


void ShadowMap::save() {
	glm::dmat4 modelView = glm::dmat4(1.0);
	glm::dmat4 projection = glm::dmat4(1.0);

	//TODO BIAS

	// Grab modelview and transformation matrices
	glGetDoublev(GL_MODELVIEW_MATRIX, &modelView[0][0]);
	glGetDoublev(GL_PROJECTION_MATRIX, &projection[0][0]);


	glMatrixMode(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE7);

	glLoadIdentity();
//	glLoadMatrixd(bias);

	// concatating all matrice into one.
	glMultMatrixd (&projection[0][0]);
	glMultMatrixd (&modelView[0][0]);

	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}


ShadowMap::ShadowMap(unsigned int width, unsigned int height):
		width_(width), height_(height) {
	LOG(info) << "ShadowMap()";

	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(GL_NEAREST));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(GL_NEAREST));

	// Remove artefact on the edges of the shadowmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLfloat>(GL_CLAMP));
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLfloat>(GL_CLAMP));

	// Create an bind texture
	glTexImage2D( GL_TEXTURE_2D, 0, static_cast<GLint>(GL_DEPTH_COMPONENT), width_, height_, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//create and bind frame buffer
	glGenFramebuffersEXT(1, &frameBufferId_);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBufferId_);

	// Instruct openGL that we won't color texture
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	// attach the texture to FBO depth attachment point
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D, textureId_, 0);

	// check FBO status
	if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) != GL_FRAMEBUFFER_COMPLETE_EXT)
		printf("GL_FRAMEBUFFER_COMPLETE_EXT failed, CANNOT use FBO\n");

	// set back window buffer
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	LOG(info) << "ShadowMap() done";
}


ShadowMap::~ShadowMap() {}
