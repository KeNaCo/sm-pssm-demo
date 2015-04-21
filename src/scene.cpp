/*
 * scene.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#include <assimp/scene.h>
#include <string>

#include "log.hpp"
#include "exceptions.hpp"
#include "scene.hpp"
#include "util.hpp"

using namespace std;


void Scene::load_meshes(aiNode* node, glm::mat4 modelMatrix) {
	for (unsigned int i=0; i < node->mNumMeshes; i++) {
		aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
		Mesh* mesh = new Mesh(aimesh, modelMatrix);
		LOG(info) << "Push mesh: " << aimesh->mName.C_Str();
		meshes[string(aimesh->mName.C_Str())] = mesh;
	}
}


void Scene::load_nodes(aiNode* node, glm::mat4 modelMatrix) {
	string nodeName = string(node->mName.C_Str());
	LOG(info) << "Load node: " << nodeName;
	LOG(debug) << "Node(" << nodeName << ").modelMatrix[" << std::endl
			   << modelMatrix[0][0] << ", " << modelMatrix[0][1] << ", " << modelMatrix[0][2] << ", " << modelMatrix[0][3] << ", " << std::endl
			   << modelMatrix[1][0] << ", " << modelMatrix[1][1] << ", " << modelMatrix[1][2] << ", " << modelMatrix[1][3] << ", " << std::endl
			   << modelMatrix[2][0] << ", " << modelMatrix[2][1] << ", " << modelMatrix[2][2] << ", " << modelMatrix[2][3] << ", " << std::endl
			   << modelMatrix[3][0] << ", " << modelMatrix[3][1] << ", " << modelMatrix[3][2] << ", " << modelMatrix[3][3] << "]";

	// compute actual modelMatrix
	// TODO: overit poradie !!!
//	glm::mat4 actModelMatrix = modelMatrix * aiMatrix4x4ToMat4_cast(node->mTransformation);
	glm::mat4 newModelMatrix = aiMatrix4x4ToMat4_cast(node->mTransformation);

	LOG(debug) << "Node(" << nodeName << ").newModelMatrix[" << std::endl
			   << newModelMatrix[0][0] << ", " << newModelMatrix[0][1] << ", " << newModelMatrix[0][2] << ", " << newModelMatrix[0][3] << ", " << std::endl
			   << newModelMatrix[1][0] << ", " << newModelMatrix[1][1] << ", " << newModelMatrix[1][2] << ", " << newModelMatrix[1][3] << ", " << std::endl
			   << newModelMatrix[2][0] << ", " << newModelMatrix[2][1] << ", " << newModelMatrix[2][2] << ", " << newModelMatrix[2][3] << ", " << std::endl
			   << newModelMatrix[3][0] << ", " << newModelMatrix[3][1] << ", " << newModelMatrix[3][2] << ", " << newModelMatrix[3][3] << "]";

	glm::mat4 actModelMatrix = newModelMatrix * modelMatrix;

	LOG(debug) << "Node(" << nodeName << ").actModelMatrix[" << std::endl
				   << actModelMatrix[0][0] << ", " << actModelMatrix[0][1] << ", " << actModelMatrix[0][2] << ", " << actModelMatrix[0][3] << ", " << std::endl
				   << actModelMatrix[1][0] << ", " << actModelMatrix[1][1] << ", " << actModelMatrix[1][2] << ", " << actModelMatrix[1][3] << ", " << std::endl
				   << actModelMatrix[2][0] << ", " << actModelMatrix[2][1] << ", " << actModelMatrix[2][2] << ", " << actModelMatrix[2][3] << ", " << std::endl
				   << actModelMatrix[3][0] << ", " << actModelMatrix[3][1] << ", " << actModelMatrix[3][2] << ", " << actModelMatrix[3][3] << "]";

	load_meshes(node, actModelMatrix);

	// check for camera nodes
	if (cameras.count(nodeName)) {
		LOG(debug) << "Camera node found!";
		cameras[nodeName]->modelMatrix(actModelMatrix);
	}

	// check for light node
	if (lights.count(nodeName)) {
		LOG(debug) << "Light node found!";
		lights[nodeName]->modelMatrix(actModelMatrix);
	}

	// load all children nodes
	for (unsigned int i=0; i < node->mNumChildren; i++) {
		load_nodes(node->mChildren[i], actModelMatrix);
	}
}



Scene::Scene(const aiScene* scene): scene(scene){

	for (unsigned int i=0; i < scene->mNumCameras; i++) {
		LOG(info) << "Push camera: " << scene->mCameras[i]->mName.C_Str();
		cameras[string(scene->mCameras[i]->mName.C_Str())] = new Camera(scene->mCameras[i]);
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

	/*	for (unsigned int i=0; i < scene->mNumMeshes; i++) {
			meshes.push_back(new Mesh(scene->mMeshes[i]));
		}*/
	load_nodes(scene->mRootNode, glm::mat4(1.f));
}

Scene::~Scene() {
	LOG(info) << "Scene::~Scene()";

	for (auto& mesh: meshes)
		delete mesh.second;

	for (auto& camera: cameras)
		delete camera.second;

	for (auto& material: materials)
		delete material;

	for (auto& light: lights)
		delete light.second;

//	delete scene;

	LOG(info) << "Scene::~Scene() done";
}

