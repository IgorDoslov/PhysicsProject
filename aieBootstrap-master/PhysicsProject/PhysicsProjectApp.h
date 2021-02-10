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

	void SetupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity);


protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Sphere* ball;
	Sphere* anotherBall;
	PhysicsScene* m_physicsScene;
	
public:
	void DrawRect();
	void SphereAndPlane();
	void DrawTable();
	void DrawBalls();
	void DrawCorners();
};