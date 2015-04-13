/*
 * texture.hpp
 *
 *  Created on: Feb 17, 2015
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_TEXTURE_HPP_
#define SUBPROJECTS__SRC_TEXTURE_HPP_


#include <glbinding/gl/gl.h>
#include <string>

#include "light.hpp"

using namespace gl;
using namespace std;

class Texture {
public:
	unsigned int id;
	unsigned int uniformId;
	unsigned int width;
	unsigned int height;
	char* data;

	void bind();

	Texture(unsigned int width=0, unsigned int height=0);
	~Texture();
};

class BMPTexture: public Texture {
public:
	char header[54];
	unsigned int dataPos;

	BMPTexture(string filename);
	~BMPTexture();
};


class ShadowMap: public Texture {
public:
	unsigned int frameBufferId;
	unsigned int depthBufferId;

	ShadowMap(unsigned int width, unsigned int height);
	~ShadowMap();
};


#endif /* SUBPROJECTS__SRC_TEXTURE_HPP_ */
