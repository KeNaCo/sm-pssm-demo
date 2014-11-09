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


Renderer_t::Renderer_t(SDL_Window* window): scene(nullptr), width(800), height(600) {
	LOG(info) << "Renderer_t constructor";

	gl = SDL_GL_CreateContext(window);

	glbinding::Binding::initialize();

	//Initialize scene
	glClearColor(0.4f, 0.6f, 0.9f, 0.0f);

	shader = new Shader("../assets/shader.vert", "../assets/shader.frag");
	float ratio = width/height;
    projectionMatrix = glm::perspective(60.0f, ratio, 0.1f, 100.f);  // Create our perspective projection matrix

    //Create square
    float* vertices = new float[18];  // Vertices for our square
    float* colors = new float[18]; // Colors for our vertices

    vertices[0] = -0.5; vertices[1] = -0.5; vertices[2] = 0.0; // Bottom left corner
    colors[0] = 1.0; colors[1] = 1.0; colors[2] = 1.0; // Bottom left corner

    vertices[3] = -0.5; vertices[4] = 0.5; vertices[5] = 0.0; // Top left corner
    colors[3] = 1.0; colors[4] = 0.0; colors[5] = 0.0; // Top left corner

    vertices[6] = 0.5; vertices[7] = 0.5; vertices[8] = 0.0; // Top Right corner
    colors[6] = 0.0; colors[7] = 1.0; colors[8] = 0.0; // Top Right corner

    vertices[9] = 0.5; vertices[10] = -0.5; vertices[11] = 0.0; // Bottom right corner
    colors[9] = 0.0; colors[10] = 0.0; colors[11] = 1.0; // Bottom right corner

    vertices[12] = -0.5; vertices[13] = -0.5; vertices[14] = 0.0; // Bottom left corner
    colors[12] = 1.0; colors[13] = 1.0; colors[14] = 1.0; // Bottom left corner

    vertices[15] = 0.5; vertices[16] = 0.5; vertices[17] = 0.0; // Top Right corner
    colors[15] = 0.0; colors[16] = 1.0; colors[17] = 0.0; // Top Right corner

    glGenVertexArrays(1, &vaoID[0]); // Create our Vertex Array Object
    glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object so we can use it

    glGenBuffers(2, &vboID[0]); // Generate our Vertex Buffer Object

    glBindBuffer(GL_ARRAY_BUFFER, vboID[0]); // Bind our Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), vertices, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(0); // Enable our Vertex Array Object

    glBindBuffer(GL_ARRAY_BUFFER, vboID[1]); // Bind our second Vertex Buffer Object
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(GLfloat), colors, GL_STATIC_DRAW); // Set the size and data of our VBO and set it to STATIC_DRAW
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0); // Set up our vertex attributes pointer
    glEnableVertexAttribArray(1); // Enable the second vertex attribute array

    glBindVertexArray(0); // Disable our Vertex Buffer Object

    delete[] vertices; // Delete our vertices from memory
    delete[] colors; // Delete our vertices from memory

	LOG(info) << "Renderer_t constructor done";
}

Renderer_t::~Renderer_t() {
	LOG(info) << "Renderer_t destructor";

	SDL_GL_DeleteContext(gl);

	LOG(info) << "Renderer_t destructor done";
}


void Renderer_t::setScene(const aiScene* scene) {
	this->scene = scene;
//	loadMeshes();
}


void Renderer_t::render() {
	LOG(info) << "Renderer_t.render()";

	glViewport(0, 0, width, height); // Set the viewport size to fill the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); // Clear required buffers

	viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.f)); // Create our view matrix
	modelMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));  // Create our model matrix


	shader->bind(); // Bind our shader

	int projectionMatrixLocation = glGetUniformLocation(shader->id(), "projectionMatrix"); // Get the location of our projection matrix in the shader
	int viewMatrixLocation = glGetUniformLocation(shader->id(), "viewMatrix"); // Get the location of our view matrix in the shader
	int modelMatrixLocation = glGetUniformLocation(shader->id(), "modelMatrix"); // Get the location of our model matrix in the shader

	glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &projectionMatrix[0][0]); // Send our projection matrix to the shader
	glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &viewMatrix[0][0]); // Send our view matrix to the shader
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &modelMatrix[0][0]); // Send our model matrix to the shader

	glBindVertexArray(vaoID[0]); // Bind our Vertex Array Object

	glDrawArrays(GL_TRIANGLES, 0, 6); // Draw our square

	glBindVertexArray(0); // Unbind our Vertex Array Object

	shader->unbind(); // Unbind our shader
	LOG(info) << "Renderer_t.render() done";
}
