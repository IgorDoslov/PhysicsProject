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
	m_tableTexture = new aie::Texture("./textures/table.png");
	m_whiteBallTexture = new aie::Texture("./textures/ball 1.png");



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
	}
	AimAndShoot(input);

	BallSunk();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

}

void PhysicsProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();



	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	//aie::Gizmos::add2DLine(glm::vec2(0, 0), glm::vec2(0, 40), glm::vec4(1, 0, 0, 1));

	// X axis = -100 to 100, Y axis = -56.25 to 56.25
	aie::Gizmos::draw2D(getWindowWidth(), getWindowHeight());//(glm::ortho<float>(-m_extents, m_extents,
		//-m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.f, 1.f));

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	//m_2dRenderer->drawLine(400, 80, 400, 640, 2, 20);
	m_2dRenderer->drawSprite(m_tableTexture, getWindowWidth()/2.f, getWindowHeight()/2.f, 
		getWindowWidth(), getWindowHeight(), 0);

	m_2dRenderer->drawSprite(m_whiteBallTexture, whiteBall->GetPosition().x, whiteBall->GetPosition().y, whiteBall->GetRadius() * 2,
		whiteBall->GetRadius() * 2);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsProjectApp::DrawTable()
{
	// bottom left
	bottomLeftBox = new Box(glm::vec2(-48, -54), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(1, 1, 0, 1));
	// bottom right
	bottomRightBox = new Box(glm::vec2(48, -54), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(1, 0, 0, 1));
	// top left
	topLeftBox = new Box(glm::vec2(-48, 45), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(0, 1, 0, 1));
	// top right
	topRightBox = new Box(glm::vec2(48, 45), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(0, 0, 1, 1));
	// right side
	rightSideBox = new Box(glm::vec2(97, -4), glm::vec2(0, 0), 0, 10, 2, 40,
		glm::vec4(1, 0, 1, 1));
	// left side
	leftSideBox = new Box(glm::vec2(-97, -4), glm::vec2(0, 0), 0, 10, 2, 40,
		glm::vec4(1, 1, 1, 1));


	m_physicsScene->AddActor(topLeftBox);
	m_physicsScene->AddActor(topRightBox);
	m_physicsScene->AddActor(bottomLeftBox);
	m_physicsScene->AddActor(bottomRightBox);
	m_physicsScene->AddActor(leftSideBox);
	m_physicsScene->AddActor(rightSideBox);

	topLeftBox->SetKinematic(1);
	topRightBox->SetKinematic(1);
	bottomLeftBox->SetKinematic(1);
	bottomRightBox->SetKinematic(1);
	leftSideBox->SetKinematic(1);
	rightSideBox->SetKinematic(1);

	topLeftBox->SetElasticity(0.6f);
	topRightBox->SetElasticity(0.6f);
	bottomLeftBox->SetElasticity(0.6f);
	bottomRightBox->SetElasticity(0.6f);
	leftSideBox->SetElasticity(0.6f);
	rightSideBox->SetElasticity(0.6f);


}

void PhysicsProjectApp::DrawBalls()
{
#pragma region CreateBall

	// White
	whiteBall = new Sphere(glm::vec2(900, 353), glm::vec2(0, 0), 1.f, m_ballRadius, glm::vec4(1, 1, 1, 1));

	// Yellow solid 1
	Sphere* ball2 = new Sphere(glm::vec2(-40, 0), glm::vec2(0, 0), 1.f, m_ballRadius, glm::vec4(1, 1, 0, 1));

	// Blue solid 2
	Sphere* ball5 = new Sphere(glm::vec2(-10, 0), glm::vec2(0, 0), 1.f, m_ballRadius, glm::vec4(0, 0, 1, 1));

	// Red solid 3
	Sphere* ball1 = new Sphere(glm::vec2(-50, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 0, 1));

	// Purple solid 4
	Sphere* ball3 = new Sphere(glm::vec2(-30, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 1, 1));

	// Green solid 6
	Sphere* ball4 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 1, 0, 1));

	// Orange solid 5
	Sphere* ball13 = new Sphere(glm::vec2(60, 10), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0.4, 0, 1));

	// Maroon solid 7;
	Sphere* ball15 = new Sphere(glm::vec2(20, 10), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0.55, 0, 0.1, 1));

	// Black 8
	Sphere* ball12 = new Sphere(glm::vec2(60, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 0, 0, 1));

	// Yellow stripe 9
	Sphere* ball8 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 1, 0, 0));

	// Blue stripe 10
	Sphere* ball11 = new Sphere(glm::vec2(50, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 0, 1, 0));

	// Red stripe 11
	Sphere* ball7 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 0, 0));

	// Purple stripe 12
	Sphere* ball9 = new Sphere(glm::vec2(30, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0, 1, 0));

	// Orange stripe 13
	Sphere* ball14 = new Sphere(glm::vec2(60, 20), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(1, 0.4, 0, 0));

	// Green stripe 14
	Sphere* ball10 = new Sphere(glm::vec2(40, 0), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0, 1, 0, 0));

	// Maroon stripe 15
	Sphere* ball16 = new Sphere(glm::vec2(30, 10), glm::vec2(0, 0), m_ballMass, m_ballRadius, glm::vec4(0.55, 0, 0.1, 0));






	CreateBall("Len", ball1);
	GetBall("Len");

#pragma endregion



	AddBallsToList(ball1);
	AddBallsToList(ball2);
	AddBallsToList(ball3);
	AddBallsToList(ball4);
	AddBallsToList(ball5);
	AddBallsToList(whiteBall);
	AddBallsToList(ball7);
	AddBallsToList(ball8);
	AddBallsToList(ball9);
	AddBallsToList(ball10);
	AddBallsToList(ball11);
	AddBallsToList(ball12);
	AddBallsToList(ball13);
	AddBallsToList(ball14);
	AddBallsToList(ball15);
	AddBallsToList(ball16);


	AddBallsToScene();

	ball1->SetElasticity(0.9f);
	ball2->SetElasticity(0.9f);
	ball3->SetElasticity(0.9f);
	ball4->SetElasticity(0.9f);
	ball5->SetElasticity(0.9f);
	whiteBall->SetElasticity(0.9f);

	ball1->SetLinearDrag(0.7f);
	ball2->SetLinearDrag(0.7f);
	ball3->SetLinearDrag(0.7f);
	ball4->SetLinearDrag(0.7f);
	ball5->SetLinearDrag(0.7f);
	whiteBall->SetLinearDrag(0.7f);

	//ball1->ApplyForce(glm::vec2(-180, 10), glm::vec2(0));
	//ball2->ApplyForce(glm::vec2(30, 180), glm::vec2(0));
	//ball3->ApplyForce(glm::vec2(10, 30), glm::vec2(0));
	//ball4->ApplyForce(glm::vec2(200, -80), glm::vec2(0));
	//ball5->ApplyForce(glm::vec2(-80, 180), glm::vec2(0));
	//ball6->ApplyForce(glm::vec2(180, -30), glm::vec2(0));

}

void PhysicsProjectApp::DrawPockets()
{
	topLeft = new Sphere(glm::vec2(-97, 47), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 0, 1));

	topCentre = new Sphere(glm::vec2(0, 50), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(1, 0, 0, 1));

	topRight = new Sphere(glm::vec2(97, 47), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(1, 0, 1, 1));

	bottomLeft = new Sphere(glm::vec2(-97, -54), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 0, 1, 1));

	bottomCentre = new Sphere(glm::vec2(0, -60), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(1, 1, 0, 1));

	bottomRight = new Sphere(glm::vec2(97, -54), glm::vec2(0, 0), 10.f, m_pocketSize, glm::vec4(0, 1, 0, 1));


	topLeft->SetKinematic(1);
	topCentre->SetKinematic(1);
	topRight->SetKinematic(1);
	bottomLeft->SetKinematic(1);
	bottomCentre->SetKinematic(1);
	bottomRight->SetKinematic(1);

	topLeft->SetTrigger(1);
	topCentre->SetTrigger(1);
	topRight->SetTrigger(1);
	bottomLeft->SetTrigger(1);
	bottomCentre->SetTrigger(1);
	bottomRight->SetTrigger(1);



	m_physicsScene->AddActor(topLeft);
	m_physicsScene->AddActor(topCentre);
	m_physicsScene->AddActor(topRight);
	m_physicsScene->AddActor(bottomLeft);
	m_physicsScene->AddActor(bottomCentre);
	m_physicsScene->AddActor(bottomRight);

	AddPocketsToList(topLeft);
	AddPocketsToList(topCentre);
	AddPocketsToList(topRight);
	AddPocketsToList(bottomLeft);
	AddPocketsToList(bottomCentre);
	AddPocketsToList(bottomRight);

}

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
		/*int xScreen, yScreen;
		a_input->getMouseXY(&xScreen, &yScreen);
		worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));*/
		worldPos.x = a_input->getMouseX();
		worldPos.y = a_input->getMouseY();

		aie::Gizmos::add2DCircle(worldPos, 5, 32, glm::vec4(0.3));
		aie::Gizmos::add2DLine(whiteBall->GetPosition(), worldPos, glm::vec4(1));

	}
	if (a_input->wasMouseButtonReleased(0))
	{
		whiteBall->ApplyForce((worldPos - whiteBall->GetPosition()), glm::vec2(0));

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

void PhysicsProjectApp::AddBallsToScene()
{
	for (auto pball : ballList)
	{
		m_physicsScene->AddActor(pball);
	}
}


bool PhysicsProjectApp::HaveAllBallsStopped()
{
	for (auto pball : ballList)
	{
		if (glm::sqrt(glm::abs(pball->GetVelocity().x) + glm::abs(pball->GetVelocity().y)) < 0.8f)
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

void PhysicsProjectApp::BallSunk()
{
	for (auto pocket : pocketList)
	{

		pocket->triggerEnter = [=](PhysicsObject* other)
		{
			std::cout << "Entered: " << other << std::endl;
			if (other == whiteBall)
			{
				whiteBall->SetPosition({ 0, 0 });
				whiteBall->SetVelocity({ 0, 0 });

			}
			if (other != whiteBall && other != blackBall8)
			{
				for (auto pBall : ballList)
				{
					if (other == pBall)
					{
						pBall->SetKinematic(1);
						pBall->SetPosition({ m_sunkPosX , m_sunkPosY });
						m_sunkPosX += 10.f;
					}
				}

			}
		};

		pocket->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };
	}

}
