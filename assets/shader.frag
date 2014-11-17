#version 130

in vec3 pass_Color;
in vec3 normal;
in vec3 light_position;

out vec4 out_Color;

//varying float diffuse;

void main(void)
{
	float diffuse = max(dot(normal, light_position), 0.0);
	out_Color = vec4(pass_Color * diffuse, 1.0);
}