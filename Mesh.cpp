#include "pch.h"
#include "Mesh.h"
#include <sstream>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::vector<ModelTexture> textures)
{
    m_indices = indices;
    m_vertices = vertices;
    m_textures = textures;

    //generate and bind vao so that it keeps the current vbo and ebo and attribs
    GL_ATTEMPT(glGenVertexArrays(1, &m_vao));
    GL_ATTEMPT(glBindVertexArray(m_vao));

    GL_ATTEMPT(glGenBuffers(1, &m_vbo));
    GL_ATTEMPT(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
    GL_ATTEMPT(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW));

    GL_ATTEMPT(glGenBuffers(1, &m_ebo));
    GL_ATTEMPT(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo));
    GL_ATTEMPT(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * m_indices.size(), m_indices.data(), GL_STATIC_DRAW));



    //tell the VAO that 1 is the position element
    SetUpAttrib(0, 3, GL_FLOAT, 0);

    //normals
    SetUpAttrib(1, 3, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4) + sizeof(glm::vec2));

    //uv
    SetUpAttrib(2, 2, GL_FLOAT, sizeof(glm::vec3) + sizeof(glm::vec4));

    
    glEnableVertexAttribArray(3);
    glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex),(void*)offsetof(Vertex, m_BoneIDs));

    // weights
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_BoneWeights));


    glBindVertexArray(0);
}

void Mesh::SetUpAttrib(int index, int count, int type, size_t offset)
{
	GL_ATTEMPT(glEnableVertexAttribArray(index));
	GL_ATTEMPT(glVertexAttribPointer(index, count, type, GL_FALSE, sizeof(Vertex), (void**)offset));

    
}

void Mesh::BindMaterials(std::shared_ptr<ShaderProgram> program ) 
{
    // Bind appropriate textures
    GLuint diffuseNr = 1;
    GLuint specularNr = 1;
    GLuint normalNr = 1;
    GLuint heightNr = 1;

    for (GLuint i = 0; i < m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
        // Retrieve texture number (the N in diffuse_textureN)
        std::stringstream ss;
        std::string number;
        std::string name = this->m_textures[i].type;

        if (name == "texture_diffuse") ss << diffuseNr++; // Transfer GLuint to stream
        else if (name == "texture_specular") ss << specularNr++; // Transfer GLuint to stream
        else if (name == "texture_normal") ss << normalNr++;
        else if (name == "texture_height") ss << heightNr++;

        number = ss.str();

        // Now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(program->Get(), ("material." + name + number).c_str()), i);
        // And finally bind the texture
        glBindTexture(GL_TEXTURE_2D, this->m_textures[i].id);
    }

    // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
    glUniform1f(glGetUniformLocation(program->Get(), "material.shininess"), 128.0f);

    // Draw mesh
    glBindVertexArray(this->m_vao);
    glDrawElements(GL_TRIANGLES, this->m_indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    //Reset textures
    for (GLuint i = 0; i <= this->m_textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

   

}

void Mesh::Bind()
{

	//TODO: don't bind mesh if it has already been bound
	GL_ATTEMPT(glBindVertexArray(m_vao));
}