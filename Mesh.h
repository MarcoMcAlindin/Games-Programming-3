#pragma once
#include "Common.h"
#include "Vertex.h"
#include "ShaderProgram.h"
#include <Importer.hpp>

struct ModelTexture
{
	aiString path;
	GLuint id;
	std::string type;
};

class Mesh
{
private:
	std::vector<Vertex> m_vertices;
	std::vector<int> m_indices;
	std::vector<ModelTexture> m_textures;
	GLuint m_vao, m_ebo, m_vbo;
	


public:

	int passNum = 0;
	Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::vector<ModelTexture> textures);
	void SetUpAttrib(int index, int count, int type, size_t offset);
	void Bind();
	void BindMaterials(std::shared_ptr<ShaderProgram> program);
	int GetIndiciesCount() { return (int)m_indices.size(); }
};


