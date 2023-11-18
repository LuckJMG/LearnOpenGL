#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>

struct Material {
	unsigned int diffuseMap {};
	unsigned int specularMap {};
	unsigned int emissionMap {};
	float shininess {};
};

struct LightSource {
	glm::vec3 position {};
	glm::vec3 color {};

	glm::vec3 ambientIntensity {};
	glm::vec3 diffuseIntensity {};
	glm::vec3 specularIntensity {};
};

class Shader {
public:
	Shader(const char* vertexPath, const char* fragmentPath);

	unsigned int getID() { return ID; };

	void use();
	void set(const std::string &name, bool value) const;
	void set(const std::string &name, int value) const;
	void set(const std::string &name, unsigned int value) const;
	void set(const std::string &name, float value) const;
	void set(const std::string &name, glm::vec2 &vector) const;
	void set(const std::string &name, glm::vec3 &vector) const;
	void set(const std::string &name, glm::vec4 &vector) const;
	void set(const std::string &name, glm::mat2 &matrix) const;
	void set(const std::string &name, glm::mat3 &matrix) const;
	void set(const std::string &name, glm::mat4 &matrix) const;

private:
	unsigned int ID;
	std::string getSourceCode(const char* path);
	void compile(const char* shaderCode, unsigned int &shaderID);
};

#endif
