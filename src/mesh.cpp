/*
 * mesh.cpp
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#include <glbinding/gl/gl.h>
#include <assimp/mesh.h>

#include "log.hpp"
#include "mesh.hpp"

using namespace gl;


/*
 * Initialize Mesh, create vao and vbos
 */
Mesh::Mesh(const aiMesh* mesh) {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	numIndices = mesh->mNumFaces * 3;

	if(mesh->HasPositions()) {
		unsigned int numVertItems = mesh->mNumVertices * 3;
		float *vertices = new float[numVertItems];

		for (unsigned int i=0; i < mesh->mNumVertices; i++) {
			vertices[i * 3] = mesh->mVertices[i].x;
			vertices[i * 3 + 1] = mesh->mVertices[i].y;
			vertices[i * 3 + 2] = mesh->mVertices[i].z;

/*			LOG(debug) << "Vertex[" << mesh->mVertices[i].x << ", "
									<< mesh->mVertices[i].y << ", "
									<< mesh->mVertices[i].z << "]"; */
		}

		glGenBuffers(1, &vbo[VERTEX_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, numVertItems * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

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

		delete[] indices;
	}

	if (mesh->HasNormals()) {
		unsigned int numNormalItems = mesh->mNumVertices * 3;
		float* normals = new float[numNormalItems];

		for (unsigned int i=0; i < mesh->mNumVertices; i++) {
			normals[i * 3] = mesh->mNormals[i].x;
			normals[i * 3 + 1] = mesh->mNormals[i].y;
			normals[i * 3 + 2] = mesh->mNormals[i].z;

/*			LOG(debug) << "Normal[" << mesh->mNormals[i].x << ", "
									<< mesh->mNormals[i].y << ", "
									<< mesh->mNormals[i].z << "]"; */
		}

		glGenBuffers(1, &vbo[NORMAL_BUFFER]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, 3 * mesh->mNumVertices * sizeof(GLfloat), normals, GL_STATIC_DRAW);

		delete normals;
	}

	glBindVertexArray(0);

	materialIndex = mesh->mMaterialIndex;
}


Mesh::~Mesh() {
	glDeleteBuffers(1, &vbo[VERTEX_BUFFER]);
	glDeleteBuffers(1, &vbo[INDEX_BUFFER]);
	glDeleteVertexArrays(1, &vao);
}


/*
 * Render current mesh
 */
void Mesh::render() {
	LOG(info) << "Mesh::render()";

	glBindVertexArray(vao);

	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VERTEX_BUFFER]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_BUFFER]);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	// Render from indices
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, NULL);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glBindVertexArray(0);

	LOG(info) << "Mesh::render() done";
}
