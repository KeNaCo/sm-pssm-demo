#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
//layout(location = 1) in vec2 vertexUV;
layout(location = 1) in vec3 vertexNormal_modelspace;

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 LightPosition_worldspace;

//out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

void main()
{
	// Vertex position in clip space
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);
	
	// Vertex position in world space
	Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;
	
	// Vector from vertex to camera in camera space
	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;
	
	// Vector from vertex to light in camera space, M is ommited because is identity
	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	// Normal of vertex in camera space
	Normal_cameraspace = ( V * M * vec4(vertexNormal_modelspace,0)).xyz;
	
//	UV = vertexUV;
}
