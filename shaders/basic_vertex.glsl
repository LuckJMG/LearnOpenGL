#version 330 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 normal;
out vec3 fragmentPosition;

void main() {
	gl_Position = projection * view * model * vec4(inPosition, 1.0);
	fragmentPosition = vec3(model * vec4(inPosition, 1.0));
	normal = inNormal;
}

