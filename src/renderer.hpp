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
#include "texture.hpp"

enum class Target { WINDOW, SHADOWMAP };

/**
 * Trieda implementuje zakladne vykreslenie sceny,
 * sluzi ako zaklad pre dalsie odvodene renderovacie triedy
 */
class Renderer {
protected:
	//view
	SDL_GLContext gl;

	// model
	Scene* scene;
	Shader* shader;


	ShadowMap* shadowMap_;

	glm::mat4 projectionMatrix; //TODO hodi sa do objektu kamery
	unsigned int activeCamera;

public:
	//TODO toto nwm ci tu musi byt, popremyslat o tom
	unsigned int width;
	unsigned int height;

	Renderer(SDL_Window* window, const char* vertexShader, const char* fragShader,
			 unsigned int width, unsigned int height);
	virtual ~Renderer();

	void setScene(Scene* scene);
	void setCamera(Camera* camera, Shader* shader);
	Camera* getActiveCamera();
	void updateProjectionMatrix(); //TODO nwm ci to treba
	virtual void render();
};

#endif /* RENDERER_H_ */
