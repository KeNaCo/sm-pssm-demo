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

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMap_->frameBufferId());
	glViewport(0, 0, width, height);



	LOG(info) << "Renderer_t.render() done";
}
