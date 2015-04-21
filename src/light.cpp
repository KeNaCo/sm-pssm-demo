/*
 * light.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: janporhincak
 */

#include <assimp/light.h>
#include <glbinding/gl/gl.h>
#include <glbinding/Binding.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "log.hpp"
#include "light.hpp"
#include "util.hpp"

using namespace gl;


/*Light::Light(): intensity_(60), color_{1.f,1.f,1.f}{
	position_ = glm::vec3(5.9, 2.5, 4.0);
	LOG(debug) << "Light(): pos[" << position_.x << ", " << position_.y << ", " << position_.z << "] "
			  << "color [" << color_.r << ", " << color_.g << ", " << color_.b << "] "
			  << "intensity " << intensity_;
}*/


Light::~Light() {}


DirectLight::DirectLight(aiLight* light) {
	name_ = std::string(light->mName.C_Str());
	intensity_ = light->mAttenuationConstant;
	color_ = aiColor3D_to_Vec3_cast(light->mColorAmbient);
	position_ = aiVector3D_to_Vec3_cast(light->mPosition);
	direction_ = aiVector3D_to_Vec3_cast(light->mDirection);

	projectionMatrix_ = glm::ortho<float>(-5,5,-5,5,-5,20); // TODO napevno?

	LOG(debug) << "DirectLight(aiLight): pos[" << position_.x << ", " << position_.y << ", " << position_.z << "] "
				  << "color [" << color_.r << ", " << color_.g << ", " << color_.b << "] "
				  << "intensity " << intensity_;
	LOG(debug) << "DirectLight(aiLight) direction[" << direction_.x << ", " << direction_.y << ", " << direction_.z << "]";
}


DirectLight::~DirectLight() {}
