#pragma once
#include "pch.h"
#include "Transform.h"
#include "Component.h"
#include "Log.h"

class Entity
{
private:

	std::vector<Component*> m_components;
	Transform* m_transform = nullptr;

public:

	Entity(std::string name);
	Entity(glm::vec3 pos, glm::quat rot, glm::vec3 scale, glm::vec3 transXYZ);

	void AddComponent(Component* c);
	template<class T> void AddComponent();
	template<class T> T* GetComponent();

	void OnUpdate(float deltaTime);
	void OnRender();

	bool isActive;
	std::string m_name = "";

	Transform* GetTransform() const { return m_transform; };
};

template<class T>
void Entity::AddComponent()
{
	T* t = new T();
	Component* c = dynamic_cast<Component*>(t);
	if (c != nullptr)
	{
		c->m_entity = this;
		m_components.push_back(c);
	}
	else
	{
		LOG_DEBUG("Can't add component, does not inherit from Component");
	}
}

//entity GetComponent function template goes HERE!
template<class T>
T* Entity::GetComponent()
{
	for (auto& c : m_components)
	{
		T* cd = dynamic_cast<T*>(c);
		if (cd != nullptr)
		{
			return cd;
		}
	}
	return nullptr;
}