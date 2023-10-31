#include "texture.h"

#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <string>

Texture::Texture(GLenum textureUnit, std::string path) {
	this->textureUnit = textureUnit;
	glActiveTexture(textureUnit);
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	setWrapping(GL_REPEAT);
	setMinMaxFilter(GL_LINEAR);

	auto colorMode = GL_RGB;
	if (path.find(".png") != std::string::npos)
		colorMode = GL_RGBA;

	stbi_set_flip_vertically_on_load(true);  
	unsigned char *rawTexture = stbi_load(path.c_str(), &width, &height, &nChannels, 0);
	if (rawTexture) {
		glTexImage2D(GL_TEXTURE_2D, 0, colorMode, width, height, 0, colorMode, GL_UNSIGNED_BYTE, rawTexture);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cerr << "Failed to load texture " << path << std::endl;

	stbi_image_free(rawTexture);
}

void Texture::setWrapping(GLenum wrappingMode) {
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrappingMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrappingMode);
}

void Texture::setMinMaxFilter(GLenum filterMode) {
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMode);

	if (filterMode == GL_LINEAR) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else if (filterMode == GL_NEAREST) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	}
}

