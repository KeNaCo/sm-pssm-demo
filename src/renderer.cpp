/*
 * renderer.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: kenaco
 */

#define GLM_FORCE_RADIANS

#include <SDL.h>
#include <SDL_video.h>
#include <boost/range/adaptor/map.hpp>
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
		scene(nullptr), activeCamera(""), width(width), height(height) {
	LOG(info) << "Renderer()";
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
	modelUniformId_ = shader->getUniform("M");
	viewUniformId_ = shader->getUniform("V");
	depthBiasmvpUniformId_ = shader->getUniform("DepthBiasMVP");
	shadowMapUniformId_ = shader->getUniform("shadowMap");
	lightInvDirectionUniformId_ = shader->getUniform("LightInvDirection_worldspace");

	shadowMap_ = new ShadowMap(512, 512);
	shadowMapShader_ = new Shader("../assets/shadow_map.vert", "../assets/shadow_map.frag");
	depthmvpUniformId_ = shadowMapShader_->getUniform("depthMVP");

	static const float quad[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	glGenBuffers(1, &qvbo);
	glBindBuffer(GL_ARRAY_BUFFER, qvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
	qshader = new Shader("../assets/passthrough.vert", "../assets/base_texture.frag");
	qTextureUniformId = qshader->getUniform("texture");

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
	activeCamera = scene->cameras.begin()->first;
	scene->cameras[activeCamera]->projectionMatrix(width, height);
}


/**
 * Metoda vracia objekt aktivnej kamery TODO implementovat prepinanie kamier?
 */
Camera* Renderer::getActiveCamera() {
	return scene->cameras[activeCamera];
}


void Renderer::render() {
	LOG(info) << "Renderer_t.render()";

//	glm::mat4 depthMVP = glm::mat4(1.f);


	glm::mat4 depthMVP;

	for (auto&& light: scene->lights | boost::adaptors::map_values) {
		glBindFramebuffer(GL_FRAMEBUFFER, shadowMap_->frameBufferId);
		glViewport(0,0,shadowMap_->width, shadowMap_->height);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		lightCamera = Camera(dynamic_cast<DirectLight*>(light));
//		depthMVP = lightCamera.mvp();

		shadowMapShader_->bind();

//		glUniformMatrix4fv(depthmvpUniformId_, 1, GL_FALSE, &depthMVP[0][0]);

		for (auto mesh: scene->meshes) {
			depthMVP = lightCamera.mvp(mesh.second->modelMatrix());
			glUniformMatrix4fv(depthmvpUniformId_, 1, GL_FALSE, &depthMVP[0][0]);

			mesh.second->render();
		}
		shadowMapShader_->unbind();

	}

	LOG(debug) << "Prvy render done!";



	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0,0, width, height);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();

//	glm::mat4 M = getActiveCamera()->modelMatrix();
//	glUniformMatrix4fv(modelUniformId_, 1, GL_FALSE, &M[0][0]);
	glm::mat4 V = getActiveCamera()->viewMatrix();
	glUniformMatrix4fv(viewUniformId_, 1, GL_FALSE, &V[0][0]);
//	glm::mat4 MVP = getActiveCamera()->mvp(width, height);
//	glUniformMatrix4fv(mvpUniformId_, 1, GL_FALSE, &MVP[0][0]);


	glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	glm::mat4 depthBiasMVP = biasMatrix * depthMVP; // TODO naivny predpoklad jedneho svetla
	glUniformMatrix4fv(depthBiasmvpUniformId_, 1, GL_FALSE, &depthBiasMVP[0][0]);

	glm::vec3 lightPos = scene->lights["light_0"]->world_position();
	glUniform3f(lightInvDirectionUniformId_, lightPos.x, lightPos.y, lightPos.z);

	glActiveTexture(GL_TEXTURE0);
	shadowMap_->bind(); // texture
	glUniform1i(shadowMapUniformId_, 0);


	for (auto item: scene->meshes) {
		Mesh* mesh = item.second;
		glUniformMatrix4fv(modelUniformId_, 1, GL_FALSE, &(mesh->modelMatrix())[0][0]);

		glm::mat4 MVP = getActiveCamera()->mvp(mesh->modelMatrix());
		glUniformMatrix4fv(mvpUniformId_, 1, GL_FALSE, &MVP[0][0]);

		mesh->render();
	}

	shader->unbind();



	// Render shadowmapy
	glViewport(0,0, width/4, height/4);

	qshader->bind();

	glActiveTexture(GL_TEXTURE0);
	shadowMap_->bind();
	glUniform1i(qTextureUniformId, 0);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, qvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);

	qshader->unbind();



	LOG(info) << "Renderer_t.render() done";
}
