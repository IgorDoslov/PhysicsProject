#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "Sphere.h"
#include "PhysicsScene.h"
#include "Input.h"
#include <vector>
#include <map>
#include <string>
#include "Box.h"

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
	void AddPocketsToList(Sphere* a_pocket);


	void AddBallsToScene();

	bool HaveAllBallsStopped();

	void BallSunk();

	void DrawTable();
	void DrawBalls();
	void DrawPockets();
protected:

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	Sphere* ball;
	Sphere* anotherBall;
	PhysicsScene* m_physicsScene;

	const float m_aspectRatio = 16.f / 9.f;
	const float m_extents = 100.f;

#pragma region Pool Balls

	Sphere* whiteBall;
	Sphere* blackBall8;
	Sphere* yellowSolid1;
	Sphere* blueSolid2;
	Sphere* redSolid3;
	Sphere* purpleSolid4;
	Sphere* orangeSolid5;
	Sphere* greenSolid6;
	Sphere* maroonSolid7;
	Sphere* yellowStripe9;
	Sphere* blueStripe10;
	Sphere* redStripe11;
	Sphere* purpleStripe12;
	Sphere* orangeStripe13;
	Sphere* greenStripe14;
	Sphere* maroonStripe15;

#pragma endregion


#pragma region Pockets

	Sphere* topLeft;
	Sphere* topCentre;
	Sphere* topRight;
	Sphere* bottomLeft;
	Sphere* bottomCentre;
	Sphere* bottomRight;

#pragma endregion


#pragma region Table

	Box* topLeftBox;
	Box* topRightBox;
	Box* bottomLeftBox;
	Box* bottomRightBox;
	Box* leftSideBox;
	Box* rightSideBox;

#pragma endregion

	float m_ballRadius = 3.f;
	float m_ballMass = 2.f;
	float m_pocketSize = 7.f;

	float m_sunkPosX = -50.f;
	float m_sunkPosY = 50.f;

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
	void SpringTest(int a_amount);
};