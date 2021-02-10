#include "Plane.h"
#include <Gizmos.h>
#include "Rigidbody.h"

Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::normalize(glm::vec2(0, 1));
	m_colour = glm::vec4(0, 1, 0, 1);
}

Plane::Plane(glm::vec2 a_normal, float a_distance) : PhysicsObject(PLANE)
{
	m_normal = glm::normalize(a_normal);
	m_distanceToOrigin = a_distance;
	m_colour = glm::vec4(0, 1, 1, 1);
}

Plane::~Plane()
{
}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
}

void Plane::Draw()
{
}

void Plane::Debug()
{
}

void Plane::ResetPosition()
{
}

void Plane::MakeGizmo()
{
	float lineSegmentLength = 300.0f; 
	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;// easy to rotate normal through 90 degrees around z
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colourFade = m_colour;
	colourFade.a = 0;
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);
	//aie::Gizmos::add2DLine(start, end, colour);
	aie::Gizmos::add2DTri(start, end, start - GetNormal() * 10.0f, GetColor(), GetColor(), colourFade);
	aie::Gizmos::add2DTri(end, end - GetNormal() * 10.0f, start - GetNormal() * 10.0f, GetColor(), colourFade, colourFade);
}

void Plane::ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact)
{
	// The position at which we'll apply the force, relative to the other objects centre of mass
	glm::vec2 localContact = a_contact - a_otherActor->GetPosition();

	// The plane never moves, so the relative velocity 
	// is just the a_otherActor's velocity at the contact point

	glm::vec2 vRel = a_otherActor->GetVelocity() + a_otherActor->GetAngularVelocity() *
		glm::vec2(-localContact.y, localContact.x);

	float velocityIntoPlane = glm::dot(vRel, m_normal);

	// This can be left as perfect elasticity for the moment
	float e = 1;

	// This is the perpendicular distance we apply the force at relative
	// to the centre of mass: Torque = F * r
	float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));

	// This will work out the 'effective mass' - a combination of the moment of inertia 
	// and mass, it will tell how much the contact point velocity will change
	float mass0 = 1.f / (1.f / a_otherActor->GetMass() + (r * r) / a_otherActor->GetMoment());

	// The plane does not move (Static) so we only use the other actor's velocity
	float j = -(1 + e) * velocityIntoPlane * mass0;
	glm::vec2 force = m_normal * j;
	a_otherActor->ApplyForce(force, a_contact - a_otherActor->GetPosition());

}
