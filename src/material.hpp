/*
 * material.hpp
 *
 *  Created on: Nov 17, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_MATERIAL_HPP_
#define SUBPROJECTS__SRC_MATERIAL_HPP_

#include <assimp/material.h>

class Material {
	float shineses;
	float diffuse[3];
	float ambient[3];
	float specular[3];

	aiMaterial* material;
public:
	Material(aiMaterial* material);
	virtual ~Material();
	void apply();
};

#endif /* SUBPROJECTS__SRC_MATERIAL_HPP_ */
