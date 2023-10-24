#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTextureCoordinates;

out vec3 color;
out vec2 textureCoordinates;

void main() {
	gl_Position = vec4(inPosition, 1.0);
	color = inColor;
	textureCoordinates = inTextureCoordinates;
}

