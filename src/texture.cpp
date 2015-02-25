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
		GLenum textureTarget, GLenum filter, GLenum attachment, bool clamp): Texture(textureTarget) {
	//init
 //	if (width > 0 && height > 0 && data != nullptr) {
		glBindTexture(textureTarget, textureId);
		glTexParameterf(textureTarget, GL_TEXTURE_MIN_FILTER, (float)filter);
		glTexParameterf(textureTarget, GL_TEXTURE_MAG_FILTER, (float)filter);

		if (clamp) {
			glTexParameterf(textureTarget, GL_TEXTURE_WRAP_S, static_cast<GLfloat>(GL_CLAMP_TO_EDGE));
			glTexParameterf(textureTarget, GL_TEXTURE_WRAP_T, static_cast<GLfloat>(GL_CLAMP_TO_EDGE));
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);

		const GLenum internalFormat = GL_DEPTH_COMPONENT16;
		const GLenum format = GL_DEPTH_COMPONENT;
		glTexImage2D(textureTarget, 0, static_cast<GLint>(internalFormat), width, height, 0, format, GL_UNSIGNED_BYTE, data); //TODO hlasi chybu ale ide
//	}

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
