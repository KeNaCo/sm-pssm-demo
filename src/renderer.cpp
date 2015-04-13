/*
 * renderer.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: kenaco
 */

#define GLM_FORCE_RADIANS

#include <SDL.h>
#include <SDL_video.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "log.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "texture.hpp"


using namespace gl;


/**
 * Inicializacia standardneho rendereru
 */
Renderer::Renderer(SDL_Window* window, const char* vertexShader, const char* fragShader, unsigned int width=800, unsigned int height=600):
		scene(nullptr), activeCamera(0), width(width), height(height) {
	//Context and gl initialization
	gl = SDL_GL_CreateContext(window);
	glbinding::Binding::initialize();

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	// Enable blending
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shader = new Shader("../assets/shader.vert", "../assets/shader.frag");
	mvpUniformId_ = shader->getUniform("MVP");
	depthBiasmvpUniformId_ = shader->getUniform("DepthBiasMVP");
	shadowMapUniformId_ = shader->getUniform("shadowMap");


	shadowMap_ = new ShadowMap(1024, 1024);
	shadowMapShader_ = new Shader("../assets/shadow_map.vert", "../assets/shadow_map.frag");
	depthmvpUniformId_ = shadowMapShader_->getUniform("depthMVP");

	LOG(info) << "Renderer() done";
}

Renderer::~Renderer() {
	LOG(info) << "Renderer::~Renderer()";

	// posobilo problemy, bolo zakomentovane TODO este otestovat
//	scene = nullptr; //zrusime ukazatel, constroler nasledne uvolni scenu
	delete shader;
	SDL_GL_DeleteContext(gl);

	LOG(info) << "Renderer::~Renderer() done";
}

//TODO sucast konstruktoru?
void Renderer::setScene(Scene* scene) {
	this->scene = scene;
}


/**
 * Metoda vracia objekt aktivnej kamery TODO implementovat prepinanie kamier?
 */
Camera* Renderer::getActiveCamera() {
	return scene->cameras[activeCamera];
}


void Renderer::render() {
	LOG(info) << "Renderer_t.render()";

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMap_->frameBufferId);
	glViewport(0,0,shadowMap_->width, shadowMap_->height);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shadowMapShader_->bind();

	glm::mat4 depthMVP = scene->lights[0]->mvp(shadowMap_->width, shadowMap_->height);
	glUniformMatrix4fv(depthmvpUniformId_, 1, GL_FALSE, &depthMVP[0][0]);


	for (auto mesh: scene->meshes) {

		mesh->render();
	}

	shadowMapShader_->unbind();

	LOG(debug) << "Prvy render done";


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0, width, height);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();

	glm::mat4 MVP = getActiveCamera()->mvp(width, height);
	glUniformMatrix4fv(mvpUniformId_, 1, GL_FALSE, &MVP[0][0]);

	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	glm::mat4 depthBiasMVP = biasMatrix * depthMVP;
	glUniformMatrix4fv(depthBiasmvpUniformId_, 1, GL_FALSE, &depthBiasMVP[0][0]);


	glActiveTexture(GL_TEXTURE0);
	shadowMap_->bind();
	glUniform1i(shadowMapUniformId_, 0);


	for (auto mesh: scene->meshes) {

		mesh->render();
	}

	shader->unbind();


	LOG(info) << "Renderer_t.render() done";
}
