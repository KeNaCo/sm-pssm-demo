#version 330 core

//in vec2 UV;
in vec4 ShadowCoord;

//uniform sampler2D myTextureSampler;
uniform sampler2DShadow shadowMap;

//out vec4 color;
layout(location = 0) out vec3 color;


void main()
{
	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);

	//Material colors
	vec3 MaterialDiffuseColor = vec3(0.5,0.5,0.5);

	float visibility = texture( shadowMap, vec3(ShadowCoord.xy, (ShadowCoord.z)/ShadowCoord.w) );
	
	color = visibility * MaterialDiffuseColor * LightColor;
}
