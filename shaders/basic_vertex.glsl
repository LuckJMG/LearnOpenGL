#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform vec3 worldLightPosition;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragmentPosition;
out vec3 lightPosition;

void main() {
	fragmentPosition = vec3(view * model * vec4(inPosition, 1.0));
	normal = mat3(transpose(inverse(view * model))) * inNormal;
	lightPosition = vec3(view * vec4(worldLightPosition, 1.0f));

	gl_Position = projection * view * model * vec4(inPosition, 1.0);
}

