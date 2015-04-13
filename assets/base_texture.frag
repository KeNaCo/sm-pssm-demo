#version 330 core

in vec2 UV;

uniform sampler2D texture;

layout(location = 0) out vec4 color;

void main() {
	color = texture2D(texture, UV);
}
