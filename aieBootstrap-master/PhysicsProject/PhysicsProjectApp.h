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
	void SetBallsElasticity();
	void SetBallsLinearDrag();

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
	aie::Texture* m_testTex;
#pragma region Pool Balls

	float m_ballRadius = 14.f;
	float m_ballMass = 2.f;
	float m_pBallElasticity = 0.9f;
	float m_pBallLinearDrag = 0.7f;

	Sphere* whiteBall;
	aie::Texture* m_whiteBallTexture;

	Sphere* blackBall8;
	aie::Texture* m_blackBall8Texture;

	Sphere* yellowSolid1;
	aie::Texture* m_yellowSolid1Texture;

	Sphere* blueSolid2;
	aie::Texture* m_blueSolid2Texture;

	Sphere* redSolid3;
	aie::Texture* m_redSolid3Texture;

	Sphere* purpleSolid4;
	aie::Texture* m_purpleSolid4Texture;

	Sphere* orangeSolid5;
	aie::Texture* m_orangeSolid5Texture;

	Sphere* greenSolid6;
	aie::Texture* m_greenSolid6Texture;

	Sphere* maroonSolid7;
	aie::Texture* m_maroonSolid7Texture;

	Sphere* yellowStripe9;
	aie::Texture* m_yellowStripe9Texture;

	Sphere* blueStripe10;
	aie::Texture* m_blueStripe10Texture;

	Sphere* redStripe11;
	aie::Texture* m_redStripe11Texture;

	Sphere* purpleStripe12;
	aie::Texture* m_purpleStripe12Texture;

	Sphere* orangeStripe13;
	aie::Texture* m_orangeStripe13Texture;

	Sphere* greenStripe14;
	aie::Texture* m_greenStripe14Texture;

	Sphere* maroonStripe15;
	aie::Texture* m_maroonStripe15Texture;

#pragma endregion


#pragma region Pockets
	
	float m_pocketSize = 22.f;

	Sphere* m_topLeft;
	Sphere* m_topCentre;
	Sphere* m_topRight;
	Sphere* m_bottomLeft;
	Sphere* m_bottomCentre;
	Sphere* m_bottomRight;

#pragma endregion


#pragma region Table

	aie::Texture* m_tableTexture;

	Box* m_topLeftBox;
	Box* m_topRightBox;
	Box* m_bottomLeftBox;
	Box* m_bottomRightBox;
	Box* m_leftSideBox;
	Box* m_rightSideBox;

#pragma endregion

	float m_sunkPosX = -80.f;
	float m_sunkPosY = 51.f;

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