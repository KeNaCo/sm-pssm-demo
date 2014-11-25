/*
 * material.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: kenaco
 */

#include <assimp/material.h>
#include <glm/glm.hpp>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>

#include "material.hpp"
#include "util.hpp"
#include "log.hpp"

using namespace gl;

Material::Material(aiMaterial* material): shineses(50), diffuse{0.2,0.2,0.2},
		ambient{0.0,0.0,0.0}, specular{1.0,1.0,1.0}, material(material) {
	LOG(info) << "Material::Material()";
/*		aiColor3D color(0.0, 0.0, 0.0);

		float diffuseFloat[4]{0.0,0.0,0.0,1.0};
		if(AI_SUCCESS != material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
			diffuse[0] = diffuseFloat[0];
			diffuse[1] = diffuseFloat[1];
			diffuse[2] = diffuseFloat[2];
			aiColor3D_to_float_cast(diffuse, color);
			LOG(debug) << "Diffuse color: [" << diffuse[0] << ", "
											 << diffuse[1] << ", "
											 << diffuse[2] << "]";
		}
	//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);

		// specular color
		if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &aiColor))
			aiColor4D_to_float_cast(color, aiColor);
		else
			color[0]=0.0f; color[1]=0.0f; color[2]=0.0f; color[3]=1.0f;
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, color);

		// ambient color
		if(AI_SUCCESS == aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &aiColor))
			aiColor4D_to_float_cast(color, aiColor);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, color);

		unsigned int max = 1;
		float shininess = 0;
		float strength = 0;
		if (AI_SUCCESS == aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS, &shininess, &max)) {
			if (aiGetMaterialFloatArray(material, AI_MATKEY_SHININESS_STRENGTH, &strength, &max) == AI_SUCCESS) {
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
			} else {
				glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
			}
		} else {
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		}*/
	LOG(info) << "Material::Material() done";
}


Material::~Material() {}


void Material::apply() {
	LOG(info) << "Material::apply()";

/*	float shineses[] = {50};
	float diffuse[] = {1.0, 0.0, 0.0};
	float ambient[] = {0.0, 0.0, 0.0};
	float specular[] = {1.0, 1.0, 1.0};*/

	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shineses);

	LOG(info) << "Material::apply() done";
}
