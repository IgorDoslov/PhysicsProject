#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <list>
#include "Rigidbody.h"
#include <iostream>

// Function pointer array for handling our collisions
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

static fn collisionFunctionArray[] = 
{
	PhysicsScene::Plane2Plane, 
	PhysicsScene::Plane2Sphere, 
	PhysicsScene::Sphere2Plane,
	PhysicsScene::Sphere2Sphere,
};

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{
}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	if (it != m_actors.end())
	{
		m_actors.erase(it);
	}
}

void PhysicsScene::Update(float dt)
{
	static std::list<PhysicsObject*> dirty; // MUST REMOVE
	static float accumulatedTime = 0.f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		for (auto pActor : m_actors)
		{
			for (auto pOther : m_actors)
			{
				if (pActor == pOther)
					continue;
				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				if (pRigid != nullptr && pRigid->CheckCollision(pOther) == true)
				{
					pRigid->ApplyForceToOther(dynamic_cast<Rigidbody*>(pOther),
						pRigid->GetVelocity()* pRigid->GetMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}

			}
		}

		dirty.clear();
	}
}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->MakeGizmo();
	}
}

void PhysicsScene::DebugScene()
{
	int count = 0;
	for (auto pActor : m_actors)
	{
		std::cout << count << " : ";
		pActor->Debug();
		count++;
	}
}

void PhysicsScene::CheckForCollision()
{
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* objOuter = m_actors[outer];
			PhysicsObject* objInner = m_actors[inner];
			int shapeID_out = objOuter->GetShapeID();
			int shapeID_out = objInner->GetShapeID();

			int functionIndex = (shapeID_out * SHAPE_COUNT) + shapeID_out;
			fn collisionFunctionPtr = collisionFunctionArray[functionIndex];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(objOuter, objInner);
			}

		}
	}
}

bool PhysicsScene::Plane2Plane(PhysicsObject*, PhysicsObject*)
{
	return false;
}

bool PhysicsScene::Plane2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return Sphere2Plane();
}

bool PhysicsScene::Sphere2Plane(PhysicsObject*, PhysicsObject*)
{
	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject*, PhysicsObject*)
{
	return false;
}
