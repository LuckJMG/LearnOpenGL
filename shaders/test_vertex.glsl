#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTextureCoordinates;

out vec2 textureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	textureCoordinates = inTextureCoordinates;
	gl_Position = projection * view * model * vec4(inPosition, 1.0f);
}

