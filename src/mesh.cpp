/*
 * mesh.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#include <glbinding/gl/gl.h>
#include <assimp/mesh.h>

#include "log.h"
#include "mesh.h"

using namespace gl;

Mesh::Mesh(const aiMesh* mesh) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	numIndices = mesh->mNumFaces * 3;

	if(mesh->HasPositions()) {
		int numVertItems = mesh->mNumVertices * 3;
		float *vertices = new float[numVertItems];

		for (unsigned int i=0; i < mesh->mNumVertices; i++) {
			vertices[i * 3] = mesh->mVertices[i].x;
			vertices[i * 3 + 1] = mesh->mVertices[i].y;
			vertices[i * 3 + 2] = mesh->mVertices[i].z;

			LOG(debug) << "Vertex[" << mesh->mVertices[i].x << ", "
									<< mesh->mVertices[i].y << ", "
									<< mesh->mVertices[i].z << "]";
		}

		glGenBuffers(1, &vbo[VERTEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertItems * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		delete[] vertices;
	}

	if(mesh->HasFaces()) {
		numIndices = mesh->mNumFaces * 3;
		unsigned int *indices = new unsigned int[numIndices];

		for (unsigned int i=0; i < mesh->mNumFaces; i++) {
			indices[i * 3] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}

		glGenBuffers(1, &vbo[INDEX_BUFFER]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[INDEX_BUFFER]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(GLuint), indices, GL_STATIC_DRAW);

//		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//		glEnableVertexAttribArray (3);

		delete[] indices;
	}

	glBindVertexArray(0);
}

Mesh::~Mesh() {
	glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
	glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
	glDeleteVertexArrays(1, &vao);
}


void Mesh::render() {
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
}
