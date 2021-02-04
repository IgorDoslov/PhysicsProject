#include "Plane.h"
#include <Gizmos.h>

Plane::Plane() : PhysicsObject(ShapeType::PLANE)
{
	m_distanceToOrigin = 0;
	m_normal = glm::vec2(0, 1);
}

Plane::Plane(glm::vec2 a_normal, float a_distance)
{
	m_normal = a_normal;
	m_distanceToOrigin = a_distance;
}

Plane::~Plane()
{
}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
}

void Plane::Draw()
{
	//floatlineSegmentLength = 300; vec2centerPoint = m_normal * m_distanceToOrigin;// easy to rotate normal through 90 degrees around z
	//vec2parallel(m_normal.y, -m_normal.x);
	//vec4colourFade = m_colour;
	//colourFade.a = 0;
	//vec2start = centerPoint +(parallel *lineSegmentLength);
	//vec2end = centerPoint -(parallel *lineSegmentLength);
	////aie::Gizmos::add2DLine(start, end, colour);
	//aie::Gizmos::add2DTri(start, end, start -m_normal*10.0f, m_colour, m_colour, colourFade);
	//aie::Gizmos::add2DTri(end, end -m_normal *10.0f, start -m_normal *10.0f, m_colour, colourFade, colourFade);
}

void Plane::ResetPosition()
{
}
