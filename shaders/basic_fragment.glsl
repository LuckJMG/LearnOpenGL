#version 330 core
out vec4 outColor;

in vec3 color;
in vec2 textureCoordinates;

// texture sampler
uniform sampler2D textureSampler0;
uniform sampler2D textureSampler1;

void main() {
	outColor = mix(texture(textureSampler0, textureCoordinates), texture(textureSampler1, textureCoordinates), 0.2);
}

