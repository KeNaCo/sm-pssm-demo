/*
 * renderer.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: kenaco
 */


#include <SDL.h>
#include <SDL_video.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glm/glm.hpp>
//#include <glm/gtc/matrix_projection.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "log.h"
#include "renderer.h"
#include "shader.h"


using namespace gl;


glm::mat4 toMat4_cast(aiMatrix4x4& matrix) {
	return glm::mat4(matrix.a1, matrix.a2, matrix.a3, matrix.a4,
					 matrix.b1, matrix.b2, matrix.b3, matrix.b4,
					 matrix.c1, matrix.c2, matrix.c3, matrix.c4,
					 matrix.d1, matrix.d2, matrix.d3, matrix.d4);
}

void Renderer_t::loadMeshes() {
	for (unsigned int i=0; i < scene->mNumMeshes; ++i) {
		meshes.push_back(new Mesh(scene->mMeshes[i]));
	}
}


void Renderer_t::renderNode(aiNode* node, aiMatrix4x4 modelMatrix) {
	modelMatrix *= node->mTransformation;

	for (unsigned int i=0; i < node->mNumMeshes; i++) {
		//nahraj material
		renderMesh(node->mMeshes[i], modelMatrix); //vykresli mesh z globalneho pola
	}

	for (unsigned int i=0; i < node->mNumChildren; i++)
		renderNode(node->mChildren[i], modelMatrix);
}


void Renderer_t::renderMesh(const unsigned int i, aiMatrix4x4 mMatrix) {
	glm::mat4 modelMatrix = toMat4_cast(mMatrix);
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));

	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

	meshes[i]->render();
}


Renderer_t::Renderer_t(SDL_Window* window): scene(nullptr), width(800), height(600) {
	LOG(info) << "Renderer_t constructor";

	gl = SDL_GL_CreateContext(window);

	glbinding::Binding::initialize();

	//Initialize scene
	glLoadIdentity(); // vycistime maticu
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);

	shader = new Shader("../assets/shader.vert", "../assets/shader.frag");
	float ratio = width/height;
    projectionMatrix = glm::perspective(60.0f, ratio, 0.1f, 100.f);  // Create our perspective projection matrix

	LOG(info) << "Renderer_t constructor done";
}

Renderer_t::~Renderer_t() {
	LOG(info) << "Renderer_t destructor";

	SDL_GL_DeleteContext(gl);

	for (auto mesh: meshes)
		delete mesh;

	LOG(info) << "Renderer_t destructor done";
}


void Renderer_t::setScene(const aiScene* scene) {
	this->scene = scene;
	loadMeshes();
}


void Renderer_t::render() {
	LOG(info) << "Renderer_t.render()";

	glViewport(0, 0, width, height); // Set the viewport size to fill the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f)); // Create our view matrix
//	modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));  // Create our model matrix


	shader->bind(); // Bind our shader

/*	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader
*/
//	for (auto mesh: meshes)
//		mesh->render();

	renderNode(scene->mRootNode, aiMatrix4x4());

	shader->unbind(); // Unbind our shader
	LOG(info) << "Renderer_t.render() done";
}
