#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Sphere.h"
#include "PhysicsScene.h"

class PhysicsProjectApp : public aie::Application {
public:

	PhysicsProjectApp();
	virtual ~PhysicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Sphere* ball;
	Sphere* anotherBall;
	PhysicsScene* m_physicsScene;

	const float m_aspectRatio = 16.f / 9.f;
	const float m_extents = 100.f;
	Sphere* whiteBall;
	glm::vec2 worldPos;
public:
	void TriggerTest();
	void DrawRect();
	void SphereAndPlane();
	void DrawTable();
	void DrawBalls();
	void DrawCorners();
	void SpringTest(int a_amount);
};