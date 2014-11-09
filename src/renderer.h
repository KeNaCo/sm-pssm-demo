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
#include "mesh.h"
#include "camera.h"

class Renderer_t {
private:
	SDL_GLContext gl;
	const aiScene* scene;
	Shader* shader;
	Camera* camera;

	glm::mat4 projectionMatrix; // Store the projection matrix
	glm::mat4 viewMatrix; // Store the view matrix
//	glm::mat4 modelMatrix; // Store the model matrix

	std::vector<Mesh*> meshes;

	void loadMeshes();
	void renderNode(aiNode* node, aiMatrix4x4);
	void renderMesh(const unsigned int i, aiMatrix4x4 mMatrix);
public:
	unsigned int width;
	unsigned int height;

	Renderer_t(SDL_Window* window);
	virtual ~Renderer_t();

	void setScene(const aiScene* scene);
	void render();
};

#endif /* RENDERER_H_ */
