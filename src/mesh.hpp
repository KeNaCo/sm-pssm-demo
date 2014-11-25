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

enum MeshEntry {
	VERTEX_BUFFER=0,
	INDEX_BUFFER,
	NORMAL_BUFFER
};

class Mesh {
	unsigned int numIndices;
	unsigned int vao;
	unsigned int vbo[3];
	unsigned int materialIndex;

public:
	unsigned int material() { return materialIndex; };

	Mesh(const aiMesh* mesh);
	virtual ~Mesh();

	void render();
};

#endif /* SUBPROJECTS__SRC_MESH_H_ */
