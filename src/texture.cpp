/*
 * texture.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Jan Porhinčák (xporhi00)
 */

#include <glbinding/gl/gl.h>

#include "log.hpp"
#include "texture.hpp"
#include "exceptions.hpp"

using namespace gl;

Texture::Texture(GLenum textureTarget): textureTarget(textureTarget), width_(0), height_(0) {
	glGenTextures(1, &textureId);
}


Texture::~Texture() {
	if (textureId) glDeleteTextures(1, &textureId);
}

ShadowMap::ShadowMap(unsigned int width, unsigned int height, unsigned char* data,
		GLenum textureTarget, GLenum filter, GLenum attachment): Texture(textureTarget) {
	//init
	if (width > 0 && height > 0 && data != nullptr) {
		glBindTexture(textureTarget, textureId);
		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, (float)filter);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, (float)filter);
		glTexImage2D(textureTarget, 0, static_cast<GLint>(GL_RGBA), width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data); //TODO hlasi chybu ale ide
	}

	//init render target
	GLenum drawBuffer;
	bool hasDepth = false;

	if (attachment == GL_DEPTH_ATTACHMENT) {
		drawBuffer = GL_NONE;
		hasDepth = true;
	} else {
		drawBuffer = attachment;
	}

	if (attachment == GL_NONE) return;

	glGenFramebuffers(1, &frameBuffer_);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer_);
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, textureTarget, textureId, 0);

	if (frameBuffer_ == 0) return;

	glDrawBuffers(1, &drawBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		throw Exception("Fail to create Frame Buffer.");
	}


}


ShadowMap::~ShadowMap() {
	glDeleteFramebuffers(1, &frameBuffer_);
}
