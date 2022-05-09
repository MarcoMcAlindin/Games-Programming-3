#pragma once
#include "Component.h"
#include "Physics.h"
#include "CollisionShape.h"

class RigidBody : public Component 
{
private:
	CollisionShape* m_shape;
	btCollisionObject* m_obj;
	btRigidBody* m_rigidBody;
	btMotionState* m_mState = nullptr;
	float mass;

public:

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	void Init(CollisionShape* shape, float mass = 1.f, const glm::vec3 localInertia = glm::vec3(1));
	virtual void UpdateParent();
	virtual void UpdateRigidBody();

	btCollisionObject* GetCollisionObject() { return m_obj; }

	btRigidBody* Get() { return m_rigidBody; }
};

