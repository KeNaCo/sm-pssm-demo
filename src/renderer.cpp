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

	shader = new Shader(vertexShader, fragShader);


/*
	// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
	static const GLfloat uvData[] = {
	    0.000059f, 1.0f-0.000004f,
	    0.000103f, 1.0f-0.336048f,
	    0.335973f, 1.0f-0.335903f,
	    1.000023f, 1.0f-0.000013f,
	    0.667979f, 1.0f-0.335851f,
	    0.999958f, 1.0f-0.336064f,
	    0.667979f, 1.0f-0.335851f,
	    0.336024f, 1.0f-0.671877f,
	    0.667969f, 1.0f-0.671889f,
	    1.000023f, 1.0f-0.000013f,
	    0.668104f, 1.0f-0.000013f,
	    0.667979f, 1.0f-0.335851f,
	    0.000059f, 1.0f-0.000004f,
	    0.335973f, 1.0f-0.335903f,
	    0.336098f, 1.0f-0.000071f,
	    0.667979f, 1.0f-0.335851f,
	    0.335973f, 1.0f-0.335903f,
	    0.336024f, 1.0f-0.671877f,
	    1.000004f, 1.0f-0.671847f,
	    0.999958f, 1.0f-0.336064f,
	    0.667979f, 1.0f-0.335851f,
	    0.668104f, 1.0f-0.000013f,
	    0.335973f, 1.0f-0.335903f,
	    0.667979f, 1.0f-0.335851f,
	    0.335973f, 1.0f-0.335903f,
	    0.668104f, 1.0f-0.000013f,
	    0.336098f, 1.0f-0.000071f,
	    0.000103f, 1.0f-0.336048f,
	    0.000004f, 1.0f-0.671870f,
	    0.336024f, 1.0f-0.671877f,
	    0.000103f, 1.0f-0.336048f,
	    0.336024f, 1.0f-0.671877f,
	    0.335973f, 1.0f-0.335903f,
	    0.667969f, 1.0f-0.671889f,
	    1.000004f, 1.0f-0.671847f,
	    0.667979f, 1.0f-0.335851f
	};

	glGenBuffers(1, &uvBuffer_);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_STATIC_DRAW);

	texture = new BMPTexture("../assets/texture.bmp");
	texture->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(GL_RGB), texture->width, texture->height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_NEAREST));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_NEAREST));

	texture->uniformId = glGetUniformLocation(shader->id(), "myTextureSampler");*/


	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);
	// Enable blending
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	light_ = new Light();

//	camera_ = new Camera(glm::vec3(4,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0), 0.1f, 100.f, 45.f);
	mvpUniformId_ = shader->getUniform("MVP");
	modelUniformId_ = shader->getUniform("M");
	viewUniformId_ = shader->getUniform("V");

	lightPositionUniformId_ = shader->getUniform("LightPosition_worldspace");
//	glUniform3f(lightPositionUniformId_, light_->position.x, light_->position.y, light_->position.z);
/*	lightColorUniformId_ = shader->getUniform("LightColor");
	glUniform3f(lightColorUniformId_, light_->color.r, light_->color.g, light_->color.b);
	lightIntensityUniformId_ = shader->getUniform("LightPower");
	glUniform1f(lightIntensityUniformId_, light_->intensity_);*/




	shadowMap_ = new ShadowMap(width, height);
/*	// Generating framebuffer
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

	texture = new Texture(width, height);
	texture->bind();
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<int>(GL_RGB), texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<int>(GL_NEAREST));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<int>(GL_NEAREST));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(GL_CLAMP_TO_EDGE));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(GL_CLAMP_TO_EDGE));

	// depth buffer
	glGenRenderbuffers(1, &depthBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBufferId);
	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->id, 0);
	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		LOG(error) << "Create framebuffer fail!";
	}
*/


	static const GLfloat quad[] = {
			-1.0f, -1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,
			 1.0f,  1.0f, 0.0f,
		};

	glGenBuffers(1, &q_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, q_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);

	q_shader = new Shader("../assets/passthrough.vert", "../assets/base_shader.frag");
	qTextureUniformId = q_shader->getUniform("renderedTexture");
	qTimeUniformId = q_shader->getUniform("time");


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
	glViewport(0,0,width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();

	glm::mat4 MVP = getActiveCamera()->mvp(width, height);
	glm::mat4 M = getActiveCamera()->modelMatrix();
	glm::mat4 V = getActiveCamera()->viewMatrix();
	glUniformMatrix4fv(mvpUniformId_, 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(modelUniformId_, 1, GL_FALSE, &M[0][0]);
	glUniformMatrix4fv(viewUniformId_, 1, GL_FALSE, &V[0][0]);

	glUniform3f(lightPositionUniformId_, light_->position.x, light_->position.y, light_->position.z);

/*	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	glUniform1i(texture->uniformId, 0); //nastavi texture uniform na texture0

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer_);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,NULL);

	glDrawArrays(GL_TRIANGLES, 0, 12*3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);*/

	for (auto mesh: scene->meshes) {

		mesh->render();
	}

	shader->unbind();




	LOG(debug) << "Prvy render done";


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0, width, height);

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	q_shader->bind();

	glActiveTexture(GL_TEXTURE0);
//	texture->bind();
	shadowMap_->bind();

	glUniform1i(qTextureUniformId, 0);
	glUniform1f(qTimeUniformId, (float)(SDL_GetTicks()));

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, q_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);


	q_shader->unbind();


	LOG(info) << "Renderer_t.render() done";
}
