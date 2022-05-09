#include "pch.h"
#include "Entity.h"
#include "Scene.h"

Entity::Entity(std::string name) {
	m_transform = new Transform();
	m_name = name;
	isActive = true;
}

Entity::Entity(glm::vec3 pos, glm::quat rot, glm::vec3 scale, glm::vec3 transXYZ)
{
	
	m_transform = new Transform(pos, rot, scale, transXYZ);
	
}

void Entity::AddComponent(Component* c)
{
	c->m_entity = this;
	m_components.push_back(c);
}

void Entity::OnUpdate(float deltaTime)
{
	if (isActive) {
		for (auto& c : m_components)
		{
			c->OnUpdate(deltaTime);
		}
	}
}

void Entity::OnRender()
{
	if (isActive) {
		for (auto& c : m_components)
		{
			c->OnRender();
		}
	}
}
