#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include <list>
#include "Rigidbody.h"
#include <iostream>
#include "Sphere.h"
#include "Plane.h"
#include "Input.h"


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
	for (auto particle : m_particles)
	{
		delete particle;
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
float timer = 0.0f;

void PhysicsScene::Update(float dt)
{
	//aie::Input* input = aie::Input::getInstance();

	timer += dt;

	static float accumulatedTime = 0.f;
	accumulatedTime += dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}

		for (auto pParticles : m_particles)
		{
			pParticles->FixedUpdate(m_gravity, m_timeStep);
		}

		accumulatedTime -= m_timeStep;

		CheckForCollision();
	}

	
	//Rigidbody* rb = dynamic_cast<Rigidbody*>(m_actors[0]);
	//Rigidbody* rb2 = dynamic_cast<Rigidbody*>(m_actors[1]);

	
	//if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))	
	//if (timer >= 0.2f)
	//{
		//Sphere* particle;
		//particle = new Sphere((rb->GetPosition()), glm::vec2(0, -10), 1.f, 1, glm::vec4(0, 1, 0, 1));
		//m_particles.push_back(particle);

		//particle->ApplyForceToOther(rb, rb->GetVelocity() * rb->GetMass());
	//	timer = 0.0f;
	//}

	
	//MoveRigidbody(rb, 87, 83, 65, 68);
	//MoveRigidbody(rb2, 87, 83, 65, 68);





	//// Move up
	//if (input->isKeyDown(aie::INPUT_KEY_UP))
	//{
	//	rb2->ApplyForce(glm::vec2(0, 1));
	//}
	//// Move down
	//if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	//{
	//	rb2->ApplyForce(glm::vec2(0, -1));
	//}
	//// Move right
	//if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	//{
	//	rb2->ApplyForce(glm::vec2(1, 0));
	//}
	//// Move left
	//if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//{
	//	rb2->ApplyForce(glm::vec2(-1, 0));
	//}
	//// Stop
	//if (input->isKeyDown(aie::INPUT_KEY_KP_0))
	//{
	//	rb2->ApplyForce(-rb2->GetVelocity());
	//}


	//std::cout << std::endl << "x: " << rb->GetPosition().x;
	//std::cout << std::endl << "y: " << rb->GetPosition().y << std::endl;
}

void PhysicsScene::Draw()
{
	for (auto pParticle : m_particles)
	{
		pParticle->MakeGizmo();
	}
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
			int shapeID_in = objInner->GetShapeID();

			int functionIndex = (shapeID_out * ShapeType::SHAPE_COUNT) + shapeID_in;
			fn collisionFunctionPtr = collisionFunctionArray[functionIndex];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(objOuter, objInner);
			}

		}
	}

	/*int pCount = m_particles.size();

	for (int outer = 0; outer < pCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < pCount; inner++)
		{
			PhysicsObject* objOuter = m_particles[outer];
			PhysicsObject* objInner = m_particles[inner];
			int shapeID_out = objOuter->GetShapeID();
			int shapeID_in = objInner->GetShapeID();

			int functionIndex = (shapeID_out * SHAPE_COUNT) + shapeID_in;
			fn collisionFunctionPtr = collisionFunctionArray[functionIndex];
			if (collisionFunctionPtr != nullptr)
			{
				collisionFunctionPtr(objOuter, objInner);
			}

		}
	}*/
}

bool PhysicsScene::Plane2Plane(PhysicsObject*, PhysicsObject*)
{
	return false;
}

bool PhysicsScene::Plane2Sphere(PhysicsObject* objPlane, PhysicsObject* objSphere)
{
	return Sphere2Plane(objSphere, objPlane);
}

bool PhysicsScene::Sphere2Plane(PhysicsObject* objSphere, PhysicsObject* objPlane)
{
	Sphere* sphere = dynamic_cast<Sphere*>(objSphere);
	Plane* plane = dynamic_cast<Plane*>(objPlane);

	// If there have a value continue below
	if (sphere != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float sphereToPlane = glm::dot(sphere->GetPosition(), collisionNormal - plane->GetDistance());
		float intersection = sphere->GetRadius() - sphereToPlane;
		float velocityOutOfPlane = glm::dot(sphere->GetVelocity(), collisionNormal);
		if (intersection > 0 && velocityOutOfPlane < 0)
		{
			sphere->ApplyForce(-sphere->GetVelocity() * sphere->GetMass());
			return true;
		}
	}

	return false;
}

bool PhysicsScene::Sphere2Sphere(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(obj1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(obj2);

	if (sphere1 != nullptr && sphere2 != nullptr)
	{
		float dist = glm::distance(sphere1->GetPosition(), sphere2->GetPosition());
		float penetration = sphere1->GetRadius() + sphere2->GetRadius() - dist;

		if (penetration > 0)
		{
			sphere1->ResolveCollision(sphere2);
			return true;
		}

	}




	return false;
}


void PhysicsScene::MoveRigidbody(Rigidbody* rb, int up, int down, int left, int right)
{
	//rb = dynamic_cast<Rigidbody*>(m_actors[playerNumber]);

	aie::Input* input = aie::Input::getInstance();

	// Move down
	if (input->isKeyDown(up))
	{
		rb->ApplyForce(glm::vec2(0, 1));
	}
	// Move up
	if (input->isKeyDown(down))
	{
		rb->ApplyForce(glm::vec2(0, -1));
	}
	// Move right
	if (input->isKeyDown(right))
	{
		rb->ApplyForce(glm::vec2(1, 0));
	}
	// Move left
	if (input->isKeyDown(left))
	{
		rb->ApplyForce(glm::vec2(-1, 0));
	}
	// Stop
	if (input->isKeyDown(aie::INPUT_KEY_E))
	{
		rb->ApplyForce(-rb->GetVelocity());
	}
}