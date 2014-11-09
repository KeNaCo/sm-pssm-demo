/*
 * mesh.h
 *
 *  Created on: Nov 9, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_MESH_H_
#define SUBPROJECTS__SRC_MESH_H_

#include <assimp/mesh.h>

enum MeshEntry {
	VERTEX_BUFFER=0,
	INDEX_BUFFER
};

class Mesh {
	unsigned int numIndices;

public:
	unsigned int vao;
	unsigned int vbo[2];

	Mesh(const aiMesh* mesh);
	virtual ~Mesh();

	void render();
};

#endif /* SUBPROJECTS__SRC_MESH_H_ */
