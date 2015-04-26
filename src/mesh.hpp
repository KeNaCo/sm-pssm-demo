/*
 * mesh.h
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_MESH_H_
#define SUBPROJECTS__SRC_MESH_H_

#include <assimp/mesh.h>
#include <glm/glm.hpp>

#include "camera.hpp"
#include "object.hpp"

enum MeshEntry {
	VERTEX_BUFFER=0,
	INDEX_BUFFER,
	NORMAL_BUFFER
};

class Mesh: public Object {
	unsigned int numIndices; //TODO potrebne?
	unsigned int vao;
	unsigned int vbo[3];
	unsigned int materialIndex;

public:

	unsigned int normalBufferId() { return vbo[NORMAL_BUFFER]; };
	unsigned int material() { return materialIndex; };
	void render();

	Mesh(string name,const unsigned int numVertices, const float* vertices,
			const unsigned int numIndices, const unsigned int* indices);
	Mesh(const aiMesh* mesh, glm::mat4 modelMatrix);
	virtual ~Mesh();
};

#endif /* SUBPROJECTS__SRC_MESH_H_ */
