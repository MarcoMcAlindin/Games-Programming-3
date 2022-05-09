#pragma once
#include "pch.h"
#include "Common.h"

class Texture
{
private:
	
	GLuint m_texture;
	std::string m_directory;
	
	GLuint Load(const std::string& directory);

	int m_width, m_height;
public:
	GLuint loadCubemap(std::vector<std::string> faces);
	Texture();
	Texture(std::string path);
	void Bind();

	


	
	
};

