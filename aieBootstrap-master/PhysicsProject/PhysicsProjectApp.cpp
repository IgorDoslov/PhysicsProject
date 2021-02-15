#include "PhysicsProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>
#include "Plane.h"
#include "PhysicsScene.h"
#include <vector>
#include "Box.h"
#include "Sphere.h"
#include "Spring.h"


PhysicsProjectApp::PhysicsProjectApp() {

}

PhysicsProjectApp::~PhysicsProjectApp() {

}

bool PhysicsProjectApp::startup() {

	// Increases the 2D line count to maximise the number of objects
	// we can draw.
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	m_tableTexture = new aie::Texture("./textures/Pool_Table_Type_1_BG Wide.png");
	m_testTex = new aie::Texture("./textures/grass.png");
	//m_whiteBallTexture = new aie::Texture("./textures/ball1.png");
	//m_whiteBallTexture = new aie::Texture(64,64,aie::Texture::RGBA);

	//#pragma region Textures
	//
	//	m_blackBall8Texture = new aie::Texture("./textures/black8.png");
	//	m_yellowSolid1Texture = new aie::Texture("./textures/yellow1test.png");
	//	m_blueSolid2Texture = new aie::Texture("./textures/blue2.png");
	//	m_redSolid3Texture = new aie::Texture("./textures/red3.png");
	//	m_purpleSolid4Texture = new aie::Texture("./textures/purple4.png");
	//	m_orangeSolid5Texture = new aie::Texture("./textures/orange5.png");
	//	m_greenSolid6Texture = new aie::Texture("./textures/green6.png");
	//	m_maroonSolid7Texture = new aie::Texture("./textures/maroon7.png");
	//	m_yellowStripe9Texture = new aie::Texture("./textures/yellowS1.png");
	//	m_blueStripe10Texture = new aie::Texture("./textures/blueS2.png");
	//	m_redStripe11Texture = new aie::Texture("./textures/redS3.png");
	//	m_purpleStripe12Texture = new aie::Texture("./textures/purpleS4.png");
	//	m_orangeStripe13Texture = new aie::Texture("./textures/orangeS5.png");
	//	m_greenStripe14Texture = new aie::Texture("./textures/greenS6.png");
	//	m_maroonStripe15Texture = new aie::Texture("./textures/maroonS7.png");
	//#pragma endregion





	m_physicsScene = new PhysicsScene();

	m_physicsScene->SetGravity(glm::vec2(0, 0));

	//SetupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)

	// Lower the value, the more accurate the simulation will be;
	// but it will increase the processing time required. If it
	// is too high it cause the sim to stutter and reduce stability.

	m_physicsScene->SetTimeStep(0.01f);

	//SetupContinuousDemo({ -40 , 0 }, 45, 40, 10);
	//DrawRect();
	//SphereAndPlane();

	//TriggerTest();
	DrawTable();
	DrawBalls();
	DrawPockets();

	//SpringTest(10);


	return true;
}

void PhysicsProjectApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void PhysicsProjectApp::update(float deltaTime) {
	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	if (HaveAllBallsStopped())
	{
		if (m_wasBallSunk == false)
		{
			std::cout << "ball sunk: " << m_wasBallSunk << std::endl;
			//ChangePlayer();
		}
	}
	AimAndShoot(input);


	//std::cout << "X: " << input->getMouseX() << " Y: " << input->getMouseY() << std::endl;
	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

}

void PhysicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	aie::Application::setBackgroundColour(0, 0.55f, 0.2f);

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	//aie::Gizmos::add2DLine(glm::vec2(0, 0), glm::vec2(0, 40), glm::vec4(1, 0, 0, 1));

	// X axis = -100 to 100, Y axis = -56.25 to 56.25
	aie::Gizmos::draw2D(getWindowWidth(), getWindowHeight());//(glm::ortho<float>(-m_extents, m_extents,
		//-m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.f, 1.f));

	char fps[32];
	sprintf_s(fps, 32, "Power: %i", m_distance);
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 12);





	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);
	m_2dRenderer->drawText(m_font, "Player 1", 20, 110);
	m_2dRenderer->drawText(m_font, "Player 2", 20, 60);


	//m_2dRenderer->drawLine(400, 80, 400, 640, 2, 20);
	//m_2dRenderer->drawSprite(m_tableTexture, getWindowWidth() / 2.f, getWindowHeight() / 2.f, getWindowWidth(), getWindowHeight(), 0);
	//m_2dRenderer->drawSprite(m_testTex, 946, 432, 10, 380, 0);


	//#pragma region DrawSpritesForBalls
	//
	//m_2dRenderer->drawSprite(m_whiteBallTexture, whiteBall->GetPosition().x, whiteBall->GetPosition().y, whiteBall->GetRadius() * 2, whiteBall->GetRadius() * 2, whiteBall->GetRotation());
	//	m_2dRenderer->drawSprite(m_blackBall8Texture, blackBall8->GetPosition().x, blackBall8->GetPosition().y, blackBall8->GetRadius() * 2, blackBall8->GetRadius() * 2, blackBall8->GetRotation());
	//	m_2dRenderer->drawSprite(m_yellowSolid1Texture, yellowSolid1->GetPosition().x, yellowSolid1->GetPosition().y, yellowSolid1->GetRadius() * 2, yellowSolid1->GetRadius() * 2, yellowSolid1->GetRotation());
	//	m_2dRenderer->drawSprite(m_blueSolid2Texture, blueSolid2->GetPosition().x, blueSolid2->GetPosition().y, blueSolid2->GetRadius() * 2, blueSolid2->GetRadius() * 2, blueSolid2->GetRotation());
	//	m_2dRenderer->drawSprite(m_redSolid3Texture, redSolid3->GetPosition().x, redSolid3->GetPosition().y, redSolid3->GetRadius() * 2, redSolid3->GetRadius() * 2, redSolid3->GetRotation());
	//	m_2dRenderer->drawSprite(m_purpleSolid4Texture, purpleSolid4->GetPosition().x, purpleSolid4->GetPosition().y, purpleSolid4->GetRadius() * 2, purpleSolid4->GetRadius() * 2, purpleSolid4->GetRotation());
	//	m_2dRenderer->drawSprite(m_orangeSolid5Texture, orangeSolid5->GetPosition().x, orangeSolid5->GetPosition().y, orangeSolid5->GetRadius() * 2, orangeSolid5->GetRadius() * 2, orangeSolid5->GetRotation());
	//	m_2dRenderer->drawSprite(m_greenSolid6Texture, greenSolid6->GetPosition().x, greenSolid6->GetPosition().y, greenSolid6->GetRadius() * 2, greenSolid6->GetRadius() * 2, greenSolid6->GetRotation());
	//	m_2dRenderer->drawSprite(m_maroonSolid7Texture, maroonSolid7->GetPosition().x, maroonSolid7->GetPosition().y, maroonSolid7->GetRadius() * 2, maroonSolid7->GetRadius() * 2, maroonSolid7->GetRotation());
	//	m_2dRenderer->drawSprite(m_yellowStripe9Texture, yellowStripe9->GetPosition().x, yellowStripe9->GetPosition().y, yellowStripe9->GetRadius() * 2, yellowStripe9->GetRadius() * 2, yellowStripe9->GetRotation());
	//	m_2dRenderer->drawSprite(m_blueStripe10Texture, blueStripe10->GetPosition().x, blueStripe10->GetPosition().y, blueStripe10->GetRadius() * 2, blueStripe10->GetRadius() * 2, blueStripe10->GetRotation());
	//	m_2dRenderer->drawSprite(m_redStripe11Texture, redStripe11->GetPosition().x, redStripe11->GetPosition().y, redStripe11->GetRadius() * 2, redStripe11->GetRadius() * 2, redStripe11->GetRotation());
	//	m_2dRenderer->drawSprite(m_purpleStripe12Texture, purpleStripe12->GetPosition().x, purpleStripe12->GetPosition().y, purpleStripe12->GetRadius() * 2, purpleStripe12->GetRadius() * 2, purpleStripe12->GetRotation());
	//	m_2dRenderer->drawSprite(m_orangeStripe13Texture, orangeStripe13->GetPosition().x, orangeStripe13->GetPosition().y, orangeStripe13->GetRadius() * 2, orangeStripe13->GetRadius() * 2, orangeStripe13->GetRotation());
	//	m_2dRenderer->drawSprite(m_greenStripe14Texture, greenStripe14->GetPosition().x, greenStripe14->GetPosition().y, greenStripe14->GetRadius() * 2, greenStripe14->GetRadius() * 2, greenStripe14->GetRotation());
	//	m_2dRenderer->drawSprite(m_maroonStripe15Texture, maroonStripe15->GetPosition().x, maroonStripe15->GetPosition().y, maroonStripe15->GetRadius() * 2, maroonStripe15->GetRadius() * 2, maroonStripe15->GetRotation());
	//
	//#pragma endregion


		// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsProjectApp::DrawTable()
{
	// bottom left
	m_bottomLeftBox = new Box(glm::vec2(300, 206), glm::vec2(0, 0), 0, 10, 186, 4,
		glm::vec4(0.6f, 0.25f, 0.01f, 1));
	// bottom right
	m_bottomRightBox = new Box(glm::vec2(725, 206), glm::vec2(0, 0), 0, 10, 186, 4,
		glm::vec4(0.6f, 0.25f, 0.01f, 1));
	// top left
	m_topLeftBox = new Box(glm::vec2(725, 657), glm::vec2(0, 0), 0, 10, 186, 4,
		glm::vec4(0.6f, 0.25f, 0.01f, 1));
	// top right
	m_topRightBox = new Box(glm::vec2(300, 657), glm::vec2(0, 0), 0, 10, 186, 4,
		glm::vec4(0.6f, 0.25f, 0.01f, 1));
	// right side
	m_rightSideBox = new Box(glm::vec2(946, 432), glm::vec2(0, 0), 0, 10, 4, 190,
		glm::vec4(0.6f, 0.25f, 0.01f, 1));
	// left side
	m_leftSideBox = new Box(glm::vec2(79, 432), glm::vec2(0, 0), 0, 10, 4, 190,
		glm::vec4(0.6f, 0.25f, 0.01f, 1));


	m_physicsScene->AddActor(m_topLeftBox);
	m_physicsScene->AddActor(m_topRightBox);
	m_physicsScene->AddActor(m_bottomLeftBox);
	m_physicsScene->AddActor(m_bottomRightBox);
	m_physicsScene->AddActor(m_leftSideBox);
	m_physicsScene->AddActor(m_rightSideBox);

	m_topLeftBox->SetKinematic(1);
	m_topRightBox->SetKinematic(1);
	m_bottomLeftBox->SetKinematic(1);
	m_bottomRightBox->SetKinematic(1);
	m_leftSideBox->SetKinematic(1);
	m_rightSideBox->SetKinematic(1);

	m_topLeftBox->SetElasticity(0.6f);
	m_topRightBox->SetElasticity(0.6f);
	m_bottomLeftBox->SetElasticity(0.6f);
	m_bottomRightBox->SetElasticity(0.6f);
	m_leftSideBox->SetElasticity(0.6f);
	m_rightSideBox->SetElasticity(0.6f);


}

void PhysicsProjectApp::DrawBalls()
{
#pragma region CreateBall

	// White
	whiteBall = new Sphere(glm::vec2(250, 435), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 1, 1, 1));

	// Yellow solid 1
	yellowSolid1 = new Sphere(glm::vec2(700, 435), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 1, 0, 1));

	// Blue solid 2
	blueSolid2 = new Sphere(glm::vec2(774, 421), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 0, 1, 1));

	// Red solid 3
	redSolid3 = new Sphere(glm::vec2(800, 463), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 0, 1));

	// Purple solid 4
	purpleSolid4 = new Sphere(glm::vec2(750, 463), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 1, 1));

	// Orange solid 5
	orangeSolid5 = new Sphere(glm::vec2(800, 406), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0.4, 0, 1));

	// Green solid 6
	greenSolid6 = new Sphere(glm::vec2(750, 407), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 1, 0, 1));

	// Maroon solid 7;
	maroonSolid7 = new Sphere(glm::vec2(800, 490), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0.55, 0, 0.1, 1));

	// Black 8
	blackBall8 = new Sphere(glm::vec2(750, 435), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 0, 0, 1));

	// Yellow stripe 9
	yellowStripe9 = new Sphere(glm::vec2(800, 435), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 1, 0, 0));

	// Blue stripe 10
	blueStripe10 = new Sphere(glm::vec2(725, 449), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 0, 1, 0));

	// Red stripe 11
	redStripe11 = new Sphere(glm::vec2(800, 378), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 0, 0));

	// Purple stripe 12
	purpleStripe12 = new Sphere(glm::vec2(774, 392), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 1, 0));

	// Orange stripe 13
	orangeStripe13 = new Sphere(glm::vec2(774, 449), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0.4, 0, 0));

	// Green stripe 14
	greenStripe14 = new Sphere(glm::vec2(774, 478), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 1, 0, 0));

	// Maroon stripe 15
	maroonStripe15 = new Sphere(glm::vec2(725, 421), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0.55, 0, 0.1, 0));






	CreateBall("Len", whiteBall);
	GetBall("Len");

#pragma endregion



	AddBallsToList(whiteBall);
	AddBallsToList(blackBall8);
	AddBallsToList(yellowSolid1);
	AddBallsToList(blueSolid2);
	AddBallsToList(redSolid3);
	AddBallsToList(purpleSolid4);
	AddBallsToList(orangeSolid5);
	AddBallsToList(greenSolid6);
	AddBallsToList(maroonSolid7);
	AddBallsToList(yellowStripe9);
	AddBallsToList(blueStripe10);
	AddBallsToList(redStripe11);
	AddBallsToList(purpleStripe12);
	AddBallsToList(orangeStripe13);
	AddBallsToList(greenStripe14);
	AddBallsToList(maroonStripe15);

	AddBallsToScene();
	SetBallsElasticity();
	SetBallsLinearDrag();
	AddSolids();
	AddStripes();




	//ball1->ApplyForce(glm::vec2(-180, 10), glm::vec2(0));
	//ball2->ApplyForce(glm::vec2(30, 180), glm::vec2(0));
	//ball3->ApplyForce(glm::vec2(10, 30), glm::vec2(0));
	//ball4->ApplyForce(glm::vec2(200, -80), glm::vec2(0));
	//ball5->ApplyForce(glm::vec2(-80, 180), glm::vec2(0));
	//ball6->ApplyForce(glm::vec2(180, -30), glm::vec2(0));

}

void PhysicsProjectApp::DrawPockets()
{
	m_topLeft = new Sphere(glm::vec2(80, 658), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));
	m_topRight = new Sphere(glm::vec2(947, 658), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));

	m_topCentre = new Sphere(glm::vec2(512, 682), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));
	m_bottomCentre = new Sphere(glm::vec2(512, 180), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));

	m_bottomLeft = new Sphere(glm::vec2(80, 207), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));
	m_bottomRight = new Sphere(glm::vec2(947, 207), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));





	m_topLeft->SetKinematic(1);
	m_topCentre->SetKinematic(1);
	m_topRight->SetKinematic(1);
	m_bottomLeft->SetKinematic(1);
	m_bottomCentre->SetKinematic(1);
	m_bottomRight->SetKinematic(1);

	m_topLeft->SetTrigger(1);
	m_topCentre->SetTrigger(1);
	m_topRight->SetTrigger(1);
	m_bottomLeft->SetTrigger(1);
	m_bottomCentre->SetTrigger(1);
	m_bottomRight->SetTrigger(1);



	m_physicsScene->AddActor(m_topLeft);
	m_physicsScene->AddActor(m_topCentre);
	m_physicsScene->AddActor(m_topRight);
	m_physicsScene->AddActor(m_bottomLeft);
	m_physicsScene->AddActor(m_bottomCentre);
	m_physicsScene->AddActor(m_bottomRight);

	AddPocketsToList(m_topLeft);
	AddPocketsToList(m_topCentre);
	AddPocketsToList(m_topRight);
	AddPocketsToList(m_bottomLeft);
	AddPocketsToList(m_bottomCentre);
	AddPocketsToList(m_bottomRight);

}

void PhysicsProjectApp::ChangePlayer()
{
	if (m_isPlayer1Turn == true)
	{
		m_isPlayer2Turn = true;
		m_isPlayer1Turn = false;

		std::cout << "Player 2's turn" << std::endl;
	}
	else
	{
		m_isPlayer1Turn = true;
		m_isPlayer2Turn = false;

		std::cout << "Player 1's turn" << std::endl;
	}
}

glm::vec2 PhysicsProjectApp::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;

	// We will move the centre of the screen to (0, 0)
	worldPos.x = getWindowWidth() / 2;
	worldPos.y = getWindowHeight() / 2;

	// Scale this according to the extents
	//worldPos.x *= 2.f * m_extents / getWindowWidth();
	//worldPos.y *= 2.f * m_extents / (m_aspectRatio * getWindowHeight());



	return worldPos;
}

void PhysicsProjectApp::AimAndShoot(aie::Input* a_input)
{

	if (a_input->isMouseButtonDown(0))
	{
		m_wasBallSunk = false;
		m_ballWasHit = false;
		/*int xScreen, yScreen;
		a_input->getMouseXY(&xScreen, &yScreen);
		worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));*/
		worldPos.x = a_input->getMouseX();
		worldPos.y = a_input->getMouseY();

		aie::Gizmos::add2DCircle(worldPos, 10, 32, glm::vec4(0.3));
		aie::Gizmos::add2DLine(whiteBall->GetPosition(), worldPos, glm::vec4(1), glm::vec4(1, 0, 0, 1));
		m_distance = glm::distance(whiteBall->GetPosition(), worldPos);
		glm::normalize(m_distance);
		//std::cout << m_distance << std::endl;

	}
	if (a_input->wasMouseButtonReleased(0))
	{
		whiteBall->ApplyForce((worldPos - whiteBall->GetPosition()), glm::vec2(0));

		whiteBall->m_collisionCallback = [=](PhysicsObject* other)
		{
			m_ballWasHit = true;
			
			BallSunk();
		if (HaveAllBallsStopped() == true && m_ballWasHit == true)
		{
			std::cout << "ball hit" << std::endl;
		}
		};

	}

}

void PhysicsProjectApp::BallSunk()
{
	for (auto pocket : pocketList)
	{

		pocket->triggerEnter = [=](PhysicsObject* other)
		{
			if (m_isFirstBallSunk == false)
			{
				// Sink white ball on the break and nothing else
				if (other == whiteBall)
				{
					whiteBall->SetPosition({ 250, 435 });
					whiteBall->SetVelocity({ 0, 0 });
					std::cout << "White ball sunk" << std::endl;
					ChangePlayer();


				}
				else if (other != whiteBall) // Sink first ball on or after break
				{
					m_isFirstBallSunk = true; // first ball has now been sunk
					for (auto pBall : ballList)
					{
						if (other == pBall)
						{
							pBall->SetKinematic(1);
							pBall->SetPosition({ m_sunkPosX , m_sunkPosY });
							m_sunkPosX += 50.f;
							m_wasBallSunk = true;
							std::cout << "First ball sunk: " << m_wasBallSunk << std::endl;

						}
					}
				}
			}
			else if (m_isFirstBallSunk == true)
			{
				if (other != whiteBall)
				{
					for (auto pBall : ballList)
					{
						if (other == pBall)
						{
							pBall->SetKinematic(1);
							pBall->SetPosition({ m_sunkPosX , m_sunkPosY });
							m_sunkPosX += 50.f;
							m_wasBallSunk = true;

							std::cout << "ball sunk: " << m_wasBallSunk << std::endl;

						}
					}
				}
				else if (other == whiteBall)
				{
					whiteBall->SetPosition({ 250, 435 });
					whiteBall->SetVelocity({ 0, 0 });
					std::cout << "White ball sunk" << std::endl;
					ChangePlayer();
				}

			}
		};

		pocket->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };
	}
	
}

void PhysicsProjectApp::AddBallsToList(Sphere* a_ball)
{
	ballList.push_back(a_ball);
}

void PhysicsProjectApp::AddPocketsToList(Sphere* a_pocket)
{
	pocketList.push_back(a_pocket);
}

void PhysicsProjectApp::AddSolids()
{
	solidBallList.push_back(yellowSolid1);
	solidBallList.push_back(blueSolid2);
	solidBallList.push_back(redSolid3);
	solidBallList.push_back(purpleSolid4);
	solidBallList.push_back(orangeSolid5);
	solidBallList.push_back(greenSolid6);
	solidBallList.push_back(maroonSolid7);

}

void PhysicsProjectApp::AddStripes()
{
	stripeBallList.push_back(yellowStripe9);
	stripeBallList.push_back(blueStripe10);
	stripeBallList.push_back(redStripe11);
	stripeBallList.push_back(purpleStripe12);
	stripeBallList.push_back(orangeStripe13);
	stripeBallList.push_back(greenStripe14);
	stripeBallList.push_back(maroonStripe15);

}

void PhysicsProjectApp::AddBallsToScene()
{
	for (auto pball : ballList)
	{
		m_physicsScene->AddActor(pball);
	}
}

void PhysicsProjectApp::SetBallsElasticity()
{
	for (auto pBall : ballList)
	{
		pBall->SetElasticity(m_pBallElasticity);
	}
}

void PhysicsProjectApp::SetBallsLinearDrag()
{
	for (auto pBall : ballList)
	{
		pBall->SetLinearDrag(m_pBallLinearDrag);
	}
}

bool PhysicsProjectApp::HaveAllBallsStopped()
{
	for (auto pball : ballList)
	{
		if (glm::sqrt(glm::abs(pball->GetVelocity().x) + glm::abs(pball->GetVelocity().y)) < 0.9f)
		{
			pball->SetVelocity(glm::vec2(0));
		}
		else
		{
			return false;
		}
	}
	return true;
}








void PhysicsProjectApp::CreateBall(const char* a_name, Sphere* a_ball)
{
	poolBalls[a_name] = a_ball;
}

Sphere* PhysicsProjectApp::GetBall(const char* a_name)
{
	auto ball = poolBalls.find(a_name);

	if (ball != poolBalls.end())
	{
		return (*ball).second;
	}
	return nullptr;
}

#pragma region Tests

void PhysicsProjectApp::SpringTest(int a_amount)
{
	Sphere* prev = nullptr;
	for (int i = 0; i < a_amount; i++)
	{
		// This will need to spawn the sphere at the bottom of the pervious one, to
		// make a pendulum that is affected by gravity
		Sphere* sphere = new Sphere(glm::vec2(i * 3, 30 - i * 5), glm::vec2(0), 10, 2, glm::vec4(0, 0, 1, 1));
		if (i == 0)
		{
			sphere->SetKinematic(true);
		}
		m_physicsScene->AddActor(sphere);
		if (prev)
		{
			m_physicsScene->AddActor(new Spring(sphere, prev, 10, 500));
		}
		prev = sphere;
	}

	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), 0.3f, 20, 8, 2);
	box->SetKinematic(true);
	m_physicsScene->AddActor(box);
}

void PhysicsProjectApp::TriggerTest()
{
	// Draw trigger before other things
	Sphere* ball1 = new Sphere(glm::vec2(10, 0), glm::vec2(0), 4, 4, glm::vec4(0.5, 0, 0, 1));
	Sphere* ball2 = new Sphere(glm::vec2(10, -5), glm::vec2(0), 4, 4, glm::vec4(0, 0.5, 0.5, 1));

	ball2->SetKinematic(true);
	ball2->SetTrigger(true);

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -30));
	m_physicsScene->AddActor(new Plane(glm::vec2(1, 0), -50));
	m_physicsScene->AddActor(new Plane(glm::vec2(-1, 0), -50));
	m_physicsScene->AddActor(new Box(glm::vec2(20, 10), glm::vec2(10, 0), 0.5, 4, 8, 4));
	m_physicsScene->AddActor(new Box(glm::vec2(-40, 10), glm::vec2(10, 0), 0.5, 4, 8, 4));

	ball2->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	ball2->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };



}

void PhysicsProjectApp::DrawRect()
{
	m_physicsScene->AddActor(new Sphere(glm::vec2(20, 10), glm::vec2(-10, -17),
		1, 3, glm::vec4(1, 0, 0, 0)));
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -1));

	Box* box1 = new Box(glm::vec2(0, 20), glm::vec2(0, 0), 1, 40, 8, 4,
		glm::vec4(1, 1, 0, 1));

	Box* box2 = new Box(glm::vec2(0, 50), glm::vec2(0, 0), 10, 40, 8, 4,
		glm::vec4(1, 0, 0, 1));


	box1->SetRotation(0.5);

	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);

	//box1->ApplyForce(glm::vec2(30, 0), glm::vec2(0));
	//box2->ApplyForce(glm::vec2(-15, 0), glm::vec2(0));

	Sphere* ball = new Sphere(glm::vec2(5, -10), glm::vec2(0), 1.f, 3, glm::vec4(0, 0, 1, 1));
	ball->SetRotation(0.5);
	m_physicsScene->AddActor(ball);
	ball->SetKinematic(true);


}

void PhysicsProjectApp::SphereAndPlane()
{
	Sphere* ball;
	ball = new Sphere(glm::vec2(-30, 20), glm::vec2(0, 0), 10.f, 7, glm::vec4(1, 0, 0, 0));
	m_physicsScene->AddActor(ball);

	Sphere* anotherBall;
	anotherBall = new Sphere(glm::vec2(40, 25), glm::vec2(0, 0), 10.f, 6, glm::vec4(0, 1, 0, 0));
	m_physicsScene->AddActor(anotherBall);

	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(0, 60), glm::vec2(0, 1), 3.f, 2, glm::vec4(1, 0, 1, 1));
	m_physicsScene->AddActor(ball2);


	ball->ApplyForce(glm::vec2(80, 0), glm::vec2(0, 0));
	anotherBall->ApplyForce(glm::vec2(30, 0), glm::vec2(0, 0));
	ball2->ApplyForce(glm::vec2(2, -30), glm::vec2(0));


	Plane* plane;
	plane = new Plane({ 1,1 }, 0.f);
	m_physicsScene->AddActor(plane);
}

#pragma endregion

