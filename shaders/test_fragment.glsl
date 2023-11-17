#version 330 core

in vec2 textureCoordinates;

uniform sampler2D diffuseMap1;

out vec4 fragmentColor;

void main() {
	fragmentColor = texture(diffuseMap1, textureCoordinates);
}

