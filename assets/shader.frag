#version 130

in vec3 pass_Color;
in vec3 normal;
in vec3 light_position;

out vec4 out_Color;

varying vec3 vertexLightHalfVector;

void main(void)
{
	// ambient
	vec4 ambientColor = gl_FrontMaterial.ambient * gl_LightSource[0].ambient +
						gl_LightModel.ambient * gl_FrontMaterial.ambient;
	
	// diffuse
	vec4 diffuseColor = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;
	
	// specular
	vec4 specularColor = gl_FrontMaterial.specular * gl_LightSource[0].specular *
						 pow(max(dot(normal, vertexLightHalfVector), 0.0),
						 	 gl_FrontMaterial.shininess);
	float diffuseValue = max(dot(normal, light_position), 0.0);
//	out_Color = pass_Color;
	out_Color = ambientColor + diffuseColor * diffuseValue + specularColor;
}