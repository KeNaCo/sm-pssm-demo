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

	//Create and initialize shader program
	shader = new Shader(vertexShader, fragShader);

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

	glm::mat4 viewMatrix = scene->cameras[activeCamera]->viewMatrix();
	glm::mat4 modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)); // TODO prerobit/odstranit

	shader->bind(); // Bind our shader

	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

	// setLight {
	glm::vec3 diffuseLight = glm::vec3(0.5, 0.5, 0.5);
	glm::vec3 ambientLight = glm::vec3(0.2, 0.2, 0.2);
	glm::vec3 specularLight = glm::vec3(0.5, 0.5, 0.5);
	glm::vec4 lightPosition = glm::vec4(6.9, 2.5, 5.0, 0.0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, &diffuseLight[0]);
	glLightfv(GL_LIGHT0, GL_AMBIENT, &ambientLight[0]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, &specularLight[0]);
	glLightfv(GL_LIGHT0, GL_POSITION, &lightPosition[0]);
	// }

	for (auto mesh: scene->meshes) {
		scene->materials[mesh->material()]->apply();
		mesh->render();
	}

	shader->unbind(); // Unbind our shader

	LOG(info) << "Renderer_t.render() done";
}


void ShadowMapRenderer::setRenderTarget(Target target) {
	if (target == Target::WINDOW) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); //TODO ta 0 sa mi celkom nepaci
		glViewport(0, 0, width, height); //TODO ok, toto si myslim ze tu ani nemusi byt, kedze to trieskame v render()
	} else if (target == Target::TEXTURE) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, shadowMap->frameBuffer()); //TODO ta 0 sa mi celkom nepaci
		glViewport(0, 0, shadowMap->width(), shadowMap->height()); //TODO ok, toto si myslim ze tu ani nemusi byt, kedze to trieskame v render()
	}
}


ShadowMapRenderer::ShadowMapRenderer(SDL_Window* window, unsigned int width, unsigned int height):
		Renderer(window, "../assets/shader.vert", "../assets/shader.frag", width, height) {
	shadowMap = new ShadowMap(width, height, NULL);
}


ShadowMapRenderer::~ShadowMapRenderer() {}


void ShadowMapRenderer::render() {
	setRenderTarget(Target::WINDOW);
	Renderer::render();
}
