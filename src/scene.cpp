/*
 * scene.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#include <assimp/scene.h>
#include <string>

#include "log.hpp"
#include "scene.hpp"
#include "exceptions.hpp"

using namespace std;


void Scene::load_meshes(aiNode* node, glm::mat4 modelMatrix) {
	for (int i=0; i < node->mNumMeshes; i++) {
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		Mesh* mesh = new Mesh(aimesh, modelMatrix);
		meshes[string(aimesh->mName.C_Str())] = mesh;
	}
}


void Scene::load_nodes(aiNode* node, glm::mat4 modelMatrix) {
	// compute actual modelMatrix
	// TODO: overit poradie !!!
	glm::mat4 actModelMatrix = modelMatrix * aiMatrix4x4ToMat4_cast(node->mTransformation);
	load_meshes(node, actModelMatrix);

	// load all children nodes
	for (int i=0; i < node->mNumChildren; i++) {
		load_nodes(node->mChildren[i], actModelMatrix);
	}
}



Scene::Scene(const aiScene* scene): scene(scene){
/*	for (unsigned int i=0; i < scene->mNumMeshes; i++) {
		meshes.push_back(new Mesh(scene->mMeshes[i]));
	}*/

	for (unsigned int i=0; i < scene->mNumCameras; i++) {
		cameras.push_back(new Camera(scene->mCameras[i]));
	}
	if (cameras.size() <= 0)
		throw Exception("Missing any camera!");

	for (unsigned int i=0; i < scene->mNumMaterials; i++) {
		materials.push_back(new Material(scene->mMaterials[i]));
	}

	for (unsigned int i=0; i < scene->mNumLights; i++) {
		LOG(info) << "Push light: " << scene->mLights[i]->mName.C_Str();
		lights[string(scene->mLights[i]->mName.C_Str())] = new DirectLight(scene->mLights[i]);
	}
}

Scene::~Scene() {
	LOG(info) << "Scene::~Scene()";

	for (auto& mesh: meshes)
		delete mesh;

	for (auto& camera: cameras)
		delete camera;

	for (auto& material: materials)
		delete material;

	for (auto& light: lights)
		delete light.second;

//	delete scene;

	LOG(info) << "Scene::~Scene() done";
}

