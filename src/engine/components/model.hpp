#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>

#include <assimp/scene.h>

#include "shader.hpp"
#include "mesh.hpp"

class Model {
public:
	Model(std::string path);
	void draw(Shader& shader);

private:
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTextures;
	std::string directory;

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material, aiTextureType type, std::string name);
};

#endif
