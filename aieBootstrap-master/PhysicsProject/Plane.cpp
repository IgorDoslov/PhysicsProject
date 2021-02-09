#include "Plane.h"
#include <Gizmos.h>

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
