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


using namespace gl;


Renderer::Renderer(SDL_Window* window) {
	LOG(info) << "Renderer_t constructor";

	gl = SDL_GL_CreateContext(window);

	glbinding::Binding::initialize();

	scene = nullptr;
	width = 800; //TODO prepracovat na automaticky update
	height = 600;
	activeCamera = 0;

	//Initialize scene rendering constants
	glLoadIdentity(); // vycistime maticu
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);

	//TODO samostatna fcia na nahravanie?
	shader = new Shader("../assets/shader.vert", "../assets/shader.frag");

	LOG(info) << "Renderer_t constructor done";
}

Renderer::~Renderer() {
	LOG(info) << "Renderer::~Renderer()";

//	scene = nullptr; //zrusime ukazatel, constroler nasledne uvolni scenu
	delete shader;
	SDL_GL_DeleteContext(gl);

	LOG(info) << "Renderer::~Renderer() done";
}


void Renderer::setScene(Scene* scene) {
	this->scene = scene;
	updateProjectionMatrix();
}


void Renderer::updateProjectionMatrix() {
	projectionMatrix = scene->cameras[activeCamera]->projectionMatrix(width, height);
}


void Renderer::render() {
	LOG(info) << "Renderer_t.render()";

	glViewport(0, 0, width, height); // Set the viewport size to fill the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers

	glm::mat4 viewMatrix = scene->cameras[activeCamera]->viewMatrix();
	glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));

	shader->bind(); // Bind our shader

	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

	for (auto mesh: scene->meshes)
		mesh->render();

	shader->unbind(); // Unbind our shader

	LOG(info) << "Renderer_t.render() done";
}
