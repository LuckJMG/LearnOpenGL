#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "../shader/shader.h"

#define MAX_BONE_INFLUENCE 4

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	glm::vec2 textureCoordinates;

	int boneIDs[MAX_BONE_INFLUENCE];
	float weights[MAX_BONE_INFLUENCE];
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void draw(Shader &shader);

private:
	unsigned int VAO, VBO, EBO;
};

#endif
