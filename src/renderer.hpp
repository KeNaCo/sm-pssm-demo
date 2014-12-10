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

	//TODO Tu su veci co sa testuju a potom sa presunu na spravne miesta
	glm::vec3 diffuseLight;
	glm::vec3 ambientLight;
	glm::vec3 specularLight;
	glm::vec4 lightPosition;

public:
	unsigned int width;
	unsigned int height;

	Renderer(SDL_Window* window);
	virtual ~Renderer();

	void setScene(Scene* scene);
	Camera* getActiveCamera();
	void updateProjectionMatrix(); //TODO nwm ci to treba
	void render();
};

#endif /* RENDERER_H_ */
