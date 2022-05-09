#pragma once
#include "pch.h"
class Fog
{
public:

	Fog();

	static Fog* m_fogInstance;
	static Fog* GetInstance();

	float GetMaxDist() { return m_maxDist; }
	float GetHeight() { return m_fogHeight; }

	float GetMinDist() { return m_minDist; }

	glm::vec3 GetColor() { return m_color; }

	void SetMaxDist(float value) { m_maxDist = value; }
	void SetMinDist(float value) { m_minDist = value; }

	void SetColor(glm::vec3 value) { m_color = value; }

	void SetHeight(float value) { m_fogHeight = value; }




private:

	float m_maxDist;
	float m_fogHeight;
	float m_minDist;
	glm::vec3 m_color;
};

