#ifndef SHADER_H
#define SHADER_H

#include <string>

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int getID() { return ID; };

	void use();
	void set(const std::string &name, bool value) const;
	void set(const std::string &name, int value) const;
	void set(const std::string &name, float value) const;

private:
	unsigned int ID;
	std::string getSourceCode(const char* path);
	void compile(const char* shaderCode, unsigned int &shaderID);
};

#endif
