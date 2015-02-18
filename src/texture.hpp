/*
 * texture.hpp
 *
 *  Created on: Feb 17, 2015
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_TEXTURE_HPP_
#define SUBPROJECTS__SRC_TEXTURE_HPP_


#include <glbinding/gl/gl.h>

using namespace gl;

/**
 *
 */
class Texture {
protected:
	GLenum textureTarget;
	unsigned int textureId;
	unsigned int width_;
	unsigned int height_;

public:
	unsigned int width() { return width_; }
	unsigned int height() { return height_; }

	Texture(GLenum textureTarget);
	virtual ~Texture();
};


/**
 *
 */
class ShadowMap: Texture {
private:
	unsigned int frameBuffer_;

public:
	unsigned int frameBuffer() { return frameBuffer_; }

	ShadowMap(GLenum textureTarget=GL_TEXTURE_2D, unsigned int width,
				  unsigned int height, unsigned char* data,
				  float filter=GL_LINEAR, GLenum attachment=GL_NONE);
	virtual ~ShadowMap();
};


#endif /* SUBPROJECTS__SRC_TEXTURE_HPP_ */
