#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <string>

class Texture {
public:
	Texture(GLenum textureUnit, std::string path);
	void setWrapping(GLenum wrappingMode);
	void setMinMaxFilter(GLenum filterMode);

private:
	unsigned int ID;
	GLenum textureUnit;
	std::string path;
	int width;
	int height;
	int nChannels;

	void bind() { 
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, ID); 
	}
};

#endif
