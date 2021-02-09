#pragma once
#include "Rigidbody.h"

class Box : public Rigidbody
{
public:
	Box(glm::vec2 a_position, glm::vec2 a_velocity, 
		float a_rotation, float a_mass, float a_width, float a_height);

	Box(glm::vec2 a_position, glm::vec2 a_velocity,
		float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);

	~Box();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void MakeGizmo();

	float GetWidth() { return m_extents.x * 2; }
	float GetHeight() { return m_extents.y * 2; }

	glm::vec2 GetExtents() const { return m_extents; }

	glm::vec2 GetLocalX() { return m_localX; }
	glm::vec2 GetLocalY() { return m_localY; }


protected:
	glm::vec2 m_extents; // The half length of the box
	glm::vec4 m_colour;

	// These will store the local x and y axes of the box based on its angle of rotation
	glm::vec2 m_localX;
	glm::vec2 m_localY;

};
