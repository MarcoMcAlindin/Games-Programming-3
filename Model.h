#pragma once
#include "Mesh.h"
#include "Vertex.h"
#include <Importer.hpp>
#include <scene.h>
#include <postprocess.h>

#define MAX_BONE_WEIGHTS 1

struct BoneData {

	int id;

	glm::mat4 offset;
};

class Model
{
private:
	std::vector<Mesh*> m_meshes;
	std::string m_directory;
	std::vector<ModelTexture> textures_loaded;

	std::unordered_map<std::string, BoneData> m_BoneDataMap;

	int m_BoneCounter = 0;

	std::vector<ModelTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	void Load();
	void processNode(aiNode* node, const aiScene* scene);
	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);
	GLuint TextureFromFile(const char* path, std::string directory);

	void VertexBoneDataToDefault(Vertex& vertex);        
	void ExtractBoneWeightForVertices(std::vector<Vertex>& vertices,aiMesh* mesh, const aiScene* scene);
	void SetVertexBoneData(Vertex& vertex, int boneID, float weight);

public:
	glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from);

	std::unordered_map<std::string, BoneData> GetBoneDataMap() { return m_BoneDataMap; }
	auto& GetOffsetMatMap() { return m_BoneDataMap; }
	int& GetBoneCount() { return m_BoneCounter; }

	Model(std::string path);
	std::vector<Mesh*> GetMeshes() { return m_meshes; };
};

