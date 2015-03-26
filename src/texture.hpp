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
class ShadowMap: public Texture {
private:
	unsigned int frameBuffer_;

public:
	unsigned int frameBuffer() { return frameBuffer_; }

	ShadowMap(unsigned int width, unsigned int height,
			GLenum textureTarget=GL_TEXTURE_2D, GLenum filter=GL_NEAREST,
			GLenum attachment=GL_DEPTH_ATTACHMENT, bool clamp=true);
	virtual ~ShadowMap();
};


#endif /* SUBPROJECTS__SRC_TEXTURE_HPP_ */
