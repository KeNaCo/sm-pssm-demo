/*
 * shader.h
 *
 *  Created on: Oct 29, 2014
 *      Author: kenaco
 */

#ifndef SUBPROJECTS__SRC_SHADER_H_
#define SUBPROJECTS__SRC_SHADER_H_

#include <glm/glm.hpp>
#include <map>
#include <string>

using namespace std;

class Shader {
	unsigned int shader_id; // The shader program identifier
	unsigned int shader_vp; // The vertex shader identifier
	unsigned int shader_fp; // The fragment shader identifier

	bool inited; // Whether or not we have initialized the shader

	map<string, unsigned int>uniforms_;

    unsigned int create_uniform(string& name);
public:
    Shader(); // Default constructor
    Shader(const char *vsFile, const char *fsFile); // Constructor for creating a shader from two shader filenames
    ~Shader(); // Deconstructor for cleaning up

    void init(const char *vsFile, const char *fsFile); // Initialize our shader file if we have to

    map<string,unsigned int>& uniforms() { return uniforms_; }
    unsigned int& uniform(string name);

    void uniform(string name, glm::mat4& matrix);
    void uniform(string name, glm::vec3& vector);

    void bind(); // Bind our GLSL shader program
    void unbind(); // Unbind our GLSL shader program

    unsigned int id(); // Get the identifier for our program
};

#endif /* SUBPROJECTS__SRC_SHADER_H_ */
