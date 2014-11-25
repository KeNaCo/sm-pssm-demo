/*
 * scene.cpp
 *
 *  Created on: Nov 14, 2014
 *      Author: kenaco
 */

#include <assimp/scene.h>

#include "log.hpp"
#include "scene.hpp"

Scene::Scene(const aiScene* scene): scene(scene){
	for (unsigned int i=0; i < scene->mNumMeshes; i++) {
		meshes.push_back(new Mesh(scene->mMeshes[i]));
	}

	for (unsigned int i=0; i < scene->mNumCameras; i++) {
		cameras.push_back(new Camera(scene->mCameras[i]));
	}

	for (unsigned int i=0; i < scene->mNumMaterials; i++) {
		materials.push_back(new Material(scene->mMaterials[i]));
	}
}

Scene::~Scene() {
	LOG(info) << "Scene::~Scene()";

	for (auto mesh: meshes)
		delete mesh;

	for (auto camera: cameras)
		delete camera;

//	delete scene;

	LOG(info) << "Scene::~Scene() done";
}

