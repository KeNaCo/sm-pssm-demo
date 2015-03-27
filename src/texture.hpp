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


class ShadowMap {
	unsigned int width_;
	unsigned int height_;
	unsigned int textureId_;
	unsigned int frameBufferId_;
	unsigned int uniform_;
public:
	unsigned int width() { return width_; }
	unsigned int height() { return height_; }
	unsigned int textureId() { return textureId_; }
	unsigned int frameBufferId() { return frameBufferId_; }
	void uniform(unsigned int uniform) { uniform_ = uniform; }
	unsigned int uniform() { return uniform_; }

	void save();

	ShadowMap(unsigned int width, unsigned int height);
	~ShadowMap();
};


#endif /* SUBPROJECTS__SRC_TEXTURE_HPP_ */
