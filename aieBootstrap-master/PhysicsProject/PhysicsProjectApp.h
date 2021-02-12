#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Sphere.h"
#include "PhysicsScene.h"
#include "Input.h"
#include <vector>
#include <map>
#include <string>

class PhysicsProjectApp : public aie::Application {
public:

	PhysicsProjectApp();
	virtual ~PhysicsProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

	void AimAndShoot(aie::Input* a_input);

	void AddBallsToList(Sphere* a_ball);

	void AddBallsToScene();

	bool HaveAllBallsStopped();

	void BallSunk();

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

	std::vector<Sphere*> ballList;
	std::vector<Sphere*> pocketList;

	std::map<const char*, Sphere*> poolBalls;
	void CreateBall(const char* a_name, Sphere* a_ball);
	Sphere* GetBall(const char* a_name);


public:
	void TriggerTest();
	void DrawRect();
	void SphereAndPlane();
	void DrawTable();
	void DrawBalls();
	void DrawCorners();
	void SpringTest(int a_amount);
};