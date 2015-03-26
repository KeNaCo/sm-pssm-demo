/*
 * light.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: janporhincak
 */

#include <assimp/light.h>

#include "light.hpp"

Light::Light(const aiLight* light): intensity(1), diffuse{0.5, 0.5, 0.5},
		ambient{0.2, 0.2, 0.2}, specular{0.5, 0.5, 0.5} {

	shadowInfo = new ShadowInfo(glm::ortho(-40,40,-40,40,-40,40));
}

Light::~Light() {
	// TODO Auto-generated destructor stub
}

