#version 130

uniform mat4 projectionMatrix;  
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;  

in vec3 in_Position;
in vec3 in_Color;
in vec3 in_Normal;

out vec3 pass_Color;
out vec3 normal;
out vec3 light_position;

varying vec3 vertexLightHalfVector;

void main(void)
{
	normal = normalize(gl_NormalMatrix * in_Normal); // Podla mna uz davno done
	light_position = gl_LightSource[0].position.xyz;
	vertexLightHalfVector = normalize(gl_LightSource[0].halfVector.xyz);
	
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(in_Position, 1.0);
	pass_Color = vec3(1.0, 0.0, 0.0);
}