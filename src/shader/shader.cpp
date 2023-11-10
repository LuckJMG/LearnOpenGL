#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	std::string vertexRawCode = Shader::getSourceCode(vertexPath);
	const char* vertexCode = vertexRawCode.c_str();
	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	Shader::compile(vertexCode, vertex);

	std::string fragmentRawCode = Shader::getSourceCode(fragmentPath);
	const char* fragmentCode = fragmentRawCode.c_str();
	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	Shader::compile(fragmentCode, fragment);

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	int success;
	char infoLog[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::set(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::set(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, unsigned int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set(const std::string &name, glm::vec2 &vector) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &vector[0]);
}

void Shader::set(const std::string &name, glm::vec3 &vector) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &vector[0]);
}

void Shader::set(const std::string &name, glm::vec4 &vector) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &vector[0]);
}

void Shader::set(const std::string &name, glm::mat2 &matrix) const {
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set(const std::string &name, glm::mat3 &matrix) const {
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set(const std::string &name, glm::mat4 &matrix) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}

std::string Shader::getSourceCode(const char* path) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::string code;

	try {
		file.open(path);

		std::stringstream stream;
		stream << file.rdbuf();

		file.close();

		code = stream.str();
	}
	catch (std::ifstream::failure &e) {
		std::cerr << "ERROR::SHADER::";
		std::cerr << path << "::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		exit(1);
	}

	return code;
}

void Shader::compile(const char* shaderCode, unsigned int &shaderID) {
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);

	int success;
	char infoLog[512];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

