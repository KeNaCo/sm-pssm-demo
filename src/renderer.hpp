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

#include "camera.hpp"

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
	unsigned int activeCamera;

	Shader* shader;
	unsigned int mvpUniformId_;
	unsigned int modelUniformId_;
	unsigned int viewUniformId_;
	unsigned int depthBiasmvpUniformId_;
	unsigned int shadowMapUniformId_;
	unsigned int lightInvDirectionUniformId_;

	Camera lightCamera;
	ShadowMap* shadowMap_;
	Shader* shadowMapShader_;
	unsigned int depthmvpUniformId_;

	unsigned int qvbo;
	Shader* qshader;
	unsigned int qTextureUniformId;


//	unsigned int lightPositionUniformId_;
//	unsigned int lightColorUniformId_;
//	unsigned int lightIntensityUniformId_;


public:
	//TODO toto nwm ci tu musi byt, popremyslat o tom
	unsigned int width;
	unsigned int height;

	Renderer(SDL_Window* window, const char* vertexShader, const char* fragShader,
			 unsigned int width, unsigned int height);
	virtual ~Renderer();

	void setScene(Scene* scene);
	Camera* getActiveCamera();

	virtual void render();
};

#endif /* RENDERER_H_ */
