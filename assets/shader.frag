#version 330 core

//in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;
in vec4 ShadowCoord;

//uniform sampler2D myTextureSampler;
uniform vec3 LightPosition_worldspace;
uniform sampler2D shadowMap;

//out vec4 color;
layout(location = 0) out vec3 color;


void main()
{
	// Light emission properties
	// You probably want to put them as uniforms
	vec3 LightColor = vec3(1,1,1);
	float LightPower = 1.0f;

	//Material colors
	vec3 MaterialDiffuseColor = vec3(0.6,0.2,0.2);
	vec3 MaterialAmbientColor = vec3(0.1,0.1,0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3,0.3,0.3);

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( Normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( LightDirection_cameraspace );
	
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendiular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp( dot( n,l ), 0,1 );
	
	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l,n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp( dot( E,R ), 0,1 );
	
	// Fixed bias, or...
	float bias = 0.005;
	// ...variable bias
	 //float bias = 0.005*tan(acos(cosTheta));
	// bias = clamp(bias, 0,0.01);
	
	float visibility = 1.0;
//	if ( texture( shadowMap, (ShadowCoord.xy/ShadowCoord.w) ).z  <  (ShadowCoord.z-bias)/ShadowCoord.w ) {
	if ( texture( shadowMap, ShadowCoord.xy ).z  <  ShadowCoord.z-bias ) {
		visibility = 0.5;
	}
	
	color = 
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		visibility * MaterialDiffuseColor * LightColor * LightPower * cosTheta +
		// Specular : reflective highlight, like a mirror
		visibility * MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha,5);
}
