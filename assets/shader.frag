#version 330 core

//in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

//uniform sampler2D myTextureSampler;
uniform vec3 LightPosition_worldspace;

//out vec4 color;
layout(location = 0) out vec3 color;

void main()
{
	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 50.0f;

	//Material colors
	//TODO: load from C++
	vec3 MaterialDiffuseColor = vec3(0.6,0.2,0.2);
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);
	
	//Distance to the light
	float distance = length( LightPosition_worldspace - Position_worldspace );

	//Normal of fragment in camera space
	vec3 n = normalize( Normal_cameraspace );
	//Direction of light from fragment to light
	vec3 l = normalize( LightDirection_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	float cosTheta = clamp( dot( n,l ), 0,1 );

	//Eye vector towards the camera
	vec3 E = normalize(EyeDirection_cameraspace);
	//Direction in which triangle reflects the light
	vec3 R = reflect(-l,n);
	//cosine between Eye vector and Reflect vector
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5) / (distance*distance);
	
	//color.a = 0.3;
	//color = texture( myTextureSampler, UV ).rgb;
}
