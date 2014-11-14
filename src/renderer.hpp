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

#include "shader.hpp"
#include "scene.hpp"

class Renderer {
private:
	SDL_GLContext gl;
	Scene* scene;
	Shader* shader;

	glm::mat4 projectionMatrix; //TODO hodi sa do objektu kamery

	unsigned int activeCamera;

//	void renderNode(aiNode* node, aiMatrix4x4); //TODO nepotrebne, assimp prepocita
												//     suradnice do globalneho priestoru
//	void renderMesh(const unsigned int i, aiMatrix4x4 mMatrix);
public:
	unsigned int width;
	unsigned int height;

	Renderer(SDL_Window* window);
	virtual ~Renderer();

	void setScene(Scene* scene);
	void updateProjectionMatrix();
	void render();
};

#endif /* RENDERER_H_ */
