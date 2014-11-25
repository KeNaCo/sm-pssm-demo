/*
 * scene.h
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_SCENE_H_
#define SUBPROJECTS__SRC_SCENE_H_

#include <assimp/scene.h>
#include <vector>

#include "mesh.hpp"
#include "camera.hpp"
#include "material.hpp"
//TODO #include "light.h"

class Scene {
	const aiScene* scene;

public:
	std::vector<Mesh*>meshes;
	std::vector<Camera*>cameras;
	std::vector<Material*>materials;

	Scene(const aiScene* scene);
	virtual ~Scene();
};

#endif /* SUBPROJECTS__SRC_SCENE_H_ */
