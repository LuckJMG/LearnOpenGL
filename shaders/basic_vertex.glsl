#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;

out vec2 textureCoordinates;

uniform mat4 transform;

void main() {
	gl_Position = transform * vec4(inPosition, 1.0);
	textureCoordinates = inTextureCoordinates;
}

