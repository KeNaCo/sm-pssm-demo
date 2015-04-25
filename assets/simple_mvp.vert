#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	mat4 MVP = projectionMatrix * viewMatrix * modelMatrix;
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}
