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
	gl = SDL_GL_CreateContext(window);
	glbinding::Binding::initialize();

	// Initialize scene rendering constants
	glLoadIdentity(); //cleaning matrix
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);
	glEnable(GL_DEPTH_TEST);

	//Create and initialize shadow map
	shadowMap_ = new ShadowMap(1024, 1024); //TODO napevno!

	//Create and initialize shader program
	shader = new Shader(vertexShader, fragShader);
	shadowMap_->uniform(shader->getUniform("ShadowMap"));

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
	updateProjectionMatrix();
}


void Renderer::setCamera(Camera* camera, Shader* shader) {
	glm::mat4 viewMatrix = camera->viewMatrix();
	glm::mat4 modelMatrix = glm::mat4(1.f); //TODO upravovatelne?

	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
}


/**
 * Metoda vracia objekt aktivnej kamery TODO implementovat prepinanie kamier?
 */
Camera* Renderer::getActiveCamera() {
	return scene->cameras[activeCamera];
}

/**
 * Upravuje projectionMatrix pri zmene rozmerov okna
 */
void Renderer::updateProjectionMatrix() {
	projectionMatrix = scene->cameras[activeCamera]->projectionMatrix(width, height);
}


void Renderer::render() {
	LOG(info) << "Renderer_t.render()";

//	glViewport(0, 0, width, height); // Set the viewport size to fill the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers

	// set render to buffer
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, shadowMap_->frameBufferId());

	//We dont use shader
	glUseProgram(0);

	//We change viwport to shadow map ratio
	glViewport(0, 0, shadowMap_->width(), shadowMap_->height());

	//disabling color mask
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

	// seting Light {
	DirectLight* light = scene->lights[0];
	light->set(nullptr, shadowMap_->width(), shadowMap_->height());
	// }

	//this avoid self shadowing
	glCullFace(GL_FRONT);

	for (auto mesh: scene->meshes) {
		scene->materials[mesh->material()]->apply();
		mesh->render();
	}

	//Save modelview/projection matrice into texture7
	shadowMap_->save();

	// set render back to camera
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

	glViewport(0,0,width,height);

	//Enabling colors
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

	// Clear previous frame values
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//using shadow shader
	shader->bind(); // Bind our shader
	glUniform1i(shadowMap_->uniform(), 7);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, shadowMap_->textureId());

	Camera* camera = scene->cameras[activeCamera];
	camera->set(nullptr, width, height);

	glCullFace(GL_BACK);

	for (auto mesh: scene->meshes) {
		scene->materials[mesh->material()]->apply();
		mesh->render();
	}

	shader->unbind(); // Unbind our shader

	LOG(info) << "Renderer_t.render() done";
}
