/*
 * scene.h
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_SCENE_H_
#define SUBPROJECTS__SRC_SCENE_H_

#include <assimp/scene.h>
#include <map>
#include <string>
#include <vector>

#include "mesh.hpp"
#include "camera.hpp"
#include "material.hpp"
#include "light.hpp"

class Scene {
	const aiScene* scene;

	void load_meshes(aiNode* node, glm::mat4 modelMatrix);
	void load_nodes(aiNode*node, glm::mat4 modelMatrix);

public:
	std::map<std::string, Mesh*>meshes;
	std::map<std::string, Camera*>cameras;
	std::vector<Material*>materials;
	std::map<std::string, Light*>lights;

	Scene() {};
	Scene(const aiScene* scene);
	~Scene();
};


class FakeScene: public Scene {
public:
	FakeScene();
	~FakeScene();
};

#endif /* SUBPROJECTS__SRC_SCENE_H_ */
