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

enum class Target { WINDOW, TEXTURE };

/**
 * Trieda implementuje zakladne vykreslenie sceny,
 * sluzi ako zaklad pre dalsie odvodene renderovacie triedy
 */
class Renderer {
private:
	//view
	SDL_GLContext gl;

	// model
	Scene* scene;
	Shader* shader;

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
	Camera* getActiveCamera();
	void updateProjectionMatrix(); //TODO nwm ci to treba
	virtual void render();
};


/**
 * Trieda implementuje vykreslovanie sceny spolu s vykreslovanim tienov pomocou
 * tienovych map.
 */
class ShadowMapRenderer: public Renderer {
private:
	ShadowMap* shadowMap;

	void setRenderTarget(Target target);

public:
	ShadowMapRenderer(SDL_Window* window, unsigned int width, unsigned int height);
	virtual ~ShadowMapRenderer();

	virtual void render();
};

#endif /* RENDERER_H_ */
