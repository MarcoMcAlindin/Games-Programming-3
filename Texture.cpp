#include "pch.h"
#include "Texture.h"
#include <stb_image.h>

Texture::Texture()
{

}

Texture::Texture(std::string path):m_texture(Load(path)), m_directory(path)
{
}

GLuint Texture::Load(const std::string& directory)
{
	stbi_set_flip_vertically_on_load(false);

	GLuint texture = 0;
	int nrChannels;
	unsigned char* data = stbi_load(directory.c_str(), &m_width, &m_height, &nrChannels, 0);
	

	if (data)
	{
		GL_ATTEMPT(glGenTextures(1, &texture));
		GL_ATTEMPT(glBindTexture(GL_TEXTURE_2D, texture));

		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GL_ATTEMPT(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		auto glChannels = GL_RGBA;
		switch (nrChannels)
		{
		case 3:
			glChannels = GL_RGB;
			break;
		case 4:
			glChannels = GL_RGBA;
			break;
		}

		GL_ATTEMPT(glTexImage2D(GL_TEXTURE_2D, 0, glChannels, m_width, m_height, 0, glChannels, GL_UNSIGNED_BYTE, data);
		GL_ATTEMPT(glGenerateMipmap(GL_TEXTURE_2D)));
		

	}
	else
	{
		LOG_DEBUG("Failed to load texture");
	}

	

	stbi_image_free(data);
	return texture;
}



void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

GLuint Texture::loadCubemap(std::vector<std::string> faces)
{
	GLuint texture = 0;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nrChannels;
	for (unsigned int x = 0; x < faces.size(); x++)
	{
		unsigned char* data = stbi_load(faces[x].c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + x, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[x] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;

}
