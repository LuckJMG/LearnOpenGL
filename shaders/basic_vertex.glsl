#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTextureCoordinates;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 textureCoordinates;
out vec3 normal;
out vec3 fragmentPosition;

void main() {
	fragmentPosition = vec3(view * model * vec4(inPosition, 1.0));
	normal = mat3(transpose(inverse(view * model))) * inNormal;
	textureCoordinates = inTextureCoordinates;

	gl_Position = projection * view * model * vec4(inPosition, 1.0);
}

