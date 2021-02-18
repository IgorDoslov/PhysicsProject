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

	void AddSolids();
	void AddStripes();
	void AddBallsToScene();
	void SetBallsElasticity();
	void SetBallsLinearDrag();

	bool HaveAllBallsStopped();

	void BallSunk();
	bool WasWhiteBallSunk(PhysicsObject* other);
	bool WasBlackBallSunk(PhysicsObject* other);
	void BallHit(PhysicsObject* other);
	void CheckBallType(PhysicsObject* other, std::vector<Sphere*> a_list);
	void SetPlayerBallType(PhysicsObject* other);
	void ChangePlayer();
	void ChangePlayerCheck();
	void PlaceBallNextToPlayer(Sphere* a_ball);
	void PoolGame(aie::Input* a_input);

	void DrawTable();
	void DrawBalls();
	void DrawPockets();

protected:

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	aie::Font* m_ballFont;
	Sphere* m_ball;
	PhysicsScene* m_physicsScene;
	std::string m_text = "as";
	
	//const float m_aspectRatio = 16.f / 9.f;
	//const float m_extents = 100.f;
	
#pragma region Pool Balls

	float m_ballRadius = 14.f;
	float m_ballMass = 1.f;
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

	Box* m_topLeftBox2;
	Box* m_topRightBox2;
	Box* m_bottomLeftBox2;
	Box* m_bottomRightBox2;
	Box* m_leftSideBox2;
	Box* m_rightSideBox2;

#pragma endregion

	float m_p1sunkPosX = 200.f;
	float m_p1sunkPosY = 120.f;
	float m_p2sunkPosX = 200.f;
	float m_p2sunkPosY = 70.f;

	bool m_isPlayer1Turn = true;
	bool m_isPlayer2Turn = false;
	bool m_isFirstBallSunk = false;
	bool m_areAllBallsSunk = false;
	bool m_wasBallSunk = false;
	bool m_ballWasHit = false;
	bool m_player1Solid = false;
	bool m_player2Solid = false;
	bool m_player1Stripe = false;
	bool m_player2Stripe = false;
	bool m_solidFound = false;
	bool m_stripeFound = false;
	bool m_ballFound = false;
	bool m_wasFirstShotTaken = false;
	bool m_hasPlayerBeenChecked = false;

	//int m_p1ShotCount = 1;
	//int m_p2ShotCount = 1;


	glm::vec2 worldPos;

	std::vector<Sphere*> ballList;
	std::vector<Sphere*> solidBallList;
	std::vector<Sphere*> stripeBallList;
	std::vector<Sphere*> pocketList;
};