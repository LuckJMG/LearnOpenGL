#version 330 core

in vec2 textureCoordinates;

uniform sampler2D diffuseMap1;

out vec4 outColor;

void main() {
	outColor = texture(diffuseMap1, textureCoordinates);
}

