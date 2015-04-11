#version 130

uniform sampler2D ShadowMap;

varying vec4 ShadowCoord;

void main()
{
	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w;
	
	// Used to lower moiré pattern and self-shadowing
	//shadowCoordinateWdivide.z += 0.0005;
	shadowCoordinateWdivide.y += 0.0005;
	
	float distanceFromLight = texture2D(ShadowMap,shadowCoordinateWdivide.st).y;
	
	
 	float shadow = 1.0;
 	if (ShadowCoord.w > 0.0)
 		shadow = distanceFromLight < shadowCoordinateWdivide.y ? 0.5 : 1.0 ;
  	
	
  	gl_FragColor =	 shadow * gl_Color;  
}
