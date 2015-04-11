/*
 * texture.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Jan Porhinčák (xporhi00)
 */

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>

#include "log.hpp"
#include "light.hpp"
#include "texture.hpp"
#include "exceptions.hpp"

using namespace gl;


void ShadowMap::save(DirectLight* light) {
	glm::dmat4 modelView = light->modelMatrix();
	glm::dmat4 projection = light->projectionMatrix(width_, height_);
	glm::dmat4 bias = glm::dmat4(0.5, 0.0, 0.0, 0.0,
								 0.0, 0.5, 0.0, 0.0,
								 0.0, 0.0, 0.5, 0.0,
								 0.5, 0.5, 0.5, 1.0);

	// Grab modelview and transformation matrices
//	glGetDoublev(GL_MODELVIEW_MATRIX, &modelView[0][0]);
//	glGetDoublev(GL_PROJECTION_MATRIX, &projection[0][0]);


	glMatrixMode(GL_TEXTURE);
	glActiveTexture(GL_TEXTURE7);

	glLoadIdentity();
	glLoadMatrixd(&bias[0][0]);

	// concatating all matrice into one.
	glMultMatrixd (&projection[0][0]);
	glMultMatrixd (&modelView[0][0]);

	// Go back to normal matrix mode
	glMatrixMode(GL_MODELVIEW);
}


ShadowMap::ShadowMap(unsigned int width, unsigned int height):
		width_(width), height_(height) {
	LOG(info) << "ShadowMap()";

	//create and bind frame buffer
	glGenFramebuffers(1, &frameBufferId_);
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, frameBufferId_);

	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);

	glTexImage2D( GL_TEXTURE_2D, 0, static_cast<GLint>(GL_RGB), width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(GL_NEAREST));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(GL_NEAREST));

	// The depth buffer
	glGenRenderbuffers(1, &depthBufferId_);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId_);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId_);

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureId_, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	// Always check that our framebuffer is ok
	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		LOG(error) << "Fuck, framebuffer je v prdeli..";
/*
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
*/

	LOG(info) << "ShadowMap() done";
}


ShadowMap::~ShadowMap() {}
