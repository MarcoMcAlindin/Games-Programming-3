#pragma once
#include "pch.h"
#include "Common.h"

#define MAX_BONE_INFLUENCE 4
struct Vertex
{
	glm::vec3 pos = glm::vec3(0, 0, 0);
	glm::vec4 color = glm::vec4(0, 0, 0, 0);
	glm::vec2 texture = glm::vec2(0, 0);
	glm::vec3 normal = glm::vec3(0, 0, 0);

	int m_BoneIDs[MAX_BONE_INFLUENCE];

	float m_BoneWeights[MAX_BONE_INFLUENCE];

	Vertex() {}

	Vertex(glm::vec3 p)
	{
		pos = p;
	}

	Vertex(glm::vec3 p, glm::vec4 c) : Vertex(p)
	{
		color = c;
	}

	Vertex(glm::vec3 p, glm::vec4 c, glm::vec2 t) : Vertex(p, c)
	{
		texture = t;
	}

	Vertex(glm::vec3 p, glm::vec4 c, glm::vec2 t, glm::vec3 n) : Vertex(p, c, t)
	{
		normal = n;
	}
};