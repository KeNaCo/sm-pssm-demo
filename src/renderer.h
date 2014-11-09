/*
 * renderer.h
 *
 *  Created on: Oct 16, 2014
 *      Author: kenaco
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#include <SDL.h>
#include <SDL_video.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>
#include "shader.h"

class Renderer_t {
private:
	SDL_GLContext gl;
	const aiScene* scene;
	Shader* shader;

	glm::mat4 projectionMatrix; // Store the projection matrix
	glm::mat4 viewMatrix; // Store the view matrix
	glm::mat4 modelMatrix; // Store the model matrix

	unsigned int vaoID[1]; // Our Vertex Array Object
	unsigned int vboID[2]; // Our Vertex Buffer Object

public:
	unsigned int width;
	unsigned int height;

	Renderer_t(SDL_Window* window);
	virtual ~Renderer_t();

	void setScene(const aiScene* scene);
	void render();
};

#endif /* RENDERER_H_ */
