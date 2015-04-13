/*
 * texture.cpp
 *
 *  Created on: Feb 17, 2015
 *      Author: Jan Porhinčák (xporhi00)
 */

#include <glbinding/gl/gl.h>
#include <glm/glm.hpp>
#include <iostream>
#include <fstream>

#include "log.hpp"
#include "light.hpp"
#include "texture.hpp"
#include "exceptions.hpp"

using namespace gl;


void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, id);
}


Texture::Texture(unsigned int width, unsigned int height):
		uniformId(0), width(width), height(height), data(nullptr) {
	glGenTextures(1, &id);
}


Texture::~Texture() {}


BMPTexture::BMPTexture(string filename) {
	ifstream file;
	file.open(filename.c_str(), ios::binary);
	file.read(header, 54);

	width = *reinterpret_cast<int*>(&header[0x12]);
	height = *reinterpret_cast<int*>(&header[0x16]);

	data = new char[width*height*3];

	file.read(data, width*height*3);
	file.close();
}




ShadowMap::ShadowMap(unsigned int width, unsigned int height): Texture(width, height) {
	LOG(info) << "ShadowMap()";

	// Generating framebuffer
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

	// bind texture and set empty image
	this->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(GL_DEPTH_COMPONENT16), width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_LINEAR));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(GL_CLAMP_TO_EDGE));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(GL_CLAMP_TO_EDGE));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, static_cast<int>(GL_EQUAL));
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, static_cast<int>(GL_COMPARE_R_TO_TEXTURE));

	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0);
	// No drawbuffer only depth
	glDrawBuffer(GL_NONE); // "1" is the size of DrawBuffers

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG(error) << "Create framebuffer fail!";
	}

	LOG(info) << "ShadowMap() done";
}


ShadowMap::~ShadowMap() {}
