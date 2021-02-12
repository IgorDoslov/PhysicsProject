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
	DrawCorners();
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
		AimAndShoot(input);
	}

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
	aie::Gizmos::draw2D(glm::ortho<float>(-m_extents, m_extents,
		-m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.f, 1.f));

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	//m_2dRenderer->drawLine(400, 80, 400, 640, 2, 20);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsProjectApp::DrawTable()
{
	// Yellow
	Box* box1 = new Box(glm::vec2(-48, -54), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(1, 1, 0, 1));
	// Red
	Box* box2 = new Box(glm::vec2(48, -54), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(1, 0, 0, 1));
	// Green
	Box* box3 = new Box(glm::vec2(-48, 54), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(0, 1, 0, 1));
	// blue
	Box* box4 = new Box(glm::vec2(48, 54), glm::vec2(0, 0), 0, 10, 38, 2,
		glm::vec4(0, 0, 1, 1));
	// Purple
	Box* box5 = new Box(glm::vec2(97, 0), glm::vec2(0, 0), 0, 10, 2, 40,
		glm::vec4(1, 0, 1, 1));
	// White
	Box* box6 = new Box(glm::vec2(-97, 0), glm::vec2(0, 0), 0, 10, 2, 40,
		glm::vec4(1, 1, 1, 1));


	m_physicsScene->AddActor(box1);
	m_physicsScene->AddActor(box2);
	m_physicsScene->AddActor(box3);
	m_physicsScene->AddActor(box4);
	m_physicsScene->AddActor(box5);
	m_physicsScene->AddActor(box6);

	box1->SetKinematic(1);
	box2->SetKinematic(1);
	box3->SetKinematic(1);
	box4->SetKinematic(1);
	box5->SetKinematic(1);
	box6->SetKinematic(1);

	box1->SetElasticity(0.6f);
	box2->SetElasticity(0.6f);
	box3->SetElasticity(0.6f);
	box4->SetElasticity(0.6f);
	box5->SetElasticity(0.6f);
	box6->SetElasticity(0.6f);


}

void PhysicsProjectApp::DrawBalls()
{
#pragma region CreateBall
	// Red
	Sphere* ball1 = new Sphere(glm::vec2(-50, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 0, 0, 1));
	// Yellow
	Sphere* ball2 = new Sphere(glm::vec2(-40, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 1, 0, 1));
	// Purple
	Sphere* ball3 = new Sphere(glm::vec2(-30, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 0, 1, 1));
	// Green
	Sphere* ball4 = new Sphere(glm::vec2(-20, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(0, 1, 0, 1));
	// Blue
	Sphere* ball5 = new Sphere(glm::vec2(-10, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(0, 0, 1, 1));
	// White
	whiteBall = new Sphere(glm::vec2(0, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 1, 1, 1));
	// Red
	Sphere* ball7 = new Sphere(glm::vec2(10, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 0, 0, 0));
	// Red clear
	Sphere* ball8 = new Sphere(glm::vec2(20, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 1, 0, 0));
	// Purple clear
	Sphere* ball9 = new Sphere(glm::vec2(30, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 0, 1, 0));
	// Green clear
	Sphere* ball10 = new Sphere(glm::vec2(40, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(0, 1, 0, 0));
	// Blue clear
	Sphere* ball11 = new Sphere(glm::vec2(50, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(0, 0, 1, 0));
	// Black
	Sphere* ball12 = new Sphere(glm::vec2(60, 0), glm::vec2(0, 0), 1.f, 4, glm::vec4(0, 0, 0, 1));
	// Orange
	Sphere* ball13 = new Sphere(glm::vec2(60, 10), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 0.4, 0, 1));
	// Orange clear
	Sphere* ball14 = new Sphere(glm::vec2(60, 20), glm::vec2(0, 0), 1.f, 4, glm::vec4(1, 0.4, 0, 0));
	// Maroon
	Sphere* ball15 = new Sphere(glm::vec2(20, 10), glm::vec2(0, 0), 1.f, 4, glm::vec4(0.55, 0, 0.1, 1));
	// Maroon clear
	Sphere* ball16 = new Sphere(glm::vec2(30, 10), glm::vec2(0, 0), 1.f, 4, glm::vec4(0.55, 0, 0.1, 0));

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

	ball1->SetLinearDrag(0.8f);
	ball2->SetLinearDrag(0.8f);
	ball3->SetLinearDrag(0.8f);
	ball4->SetLinearDrag(0.8f);
	ball5->SetLinearDrag(0.8f);
	whiteBall->SetLinearDrag(0.8f);

	//ball1->ApplyForce(glm::vec2(-180, 10), glm::vec2(0));
	//ball2->ApplyForce(glm::vec2(30, 180), glm::vec2(0));
	//ball3->ApplyForce(glm::vec2(10, 30), glm::vec2(0));
	//ball4->ApplyForce(glm::vec2(200, -80), glm::vec2(0));
	//ball5->ApplyForce(glm::vec2(-80, 180), glm::vec2(0));
	//ball6->ApplyForce(glm::vec2(180, -30), glm::vec2(0));

}

void PhysicsProjectApp::DrawCorners()
{
	// Red
	Sphere* ball1 = new Sphere(glm::vec2(0, 60), glm::vec2(0, 0), 10.f, 8, glm::vec4(1, 0, 0, 1));
	// Yellow
	Sphere* ball2 = new Sphere(glm::vec2(0, -60), glm::vec2(0, 0), 10.f, 8, glm::vec4(0, 0, 0, 1));
	// Purple
	Sphere* ball3 = new Sphere(glm::vec2(97, 52), glm::vec2(0, 0), 10.f, 8, glm::vec4(0, 0, 0, 1));
	// Green
	Sphere* ball4 = new Sphere(glm::vec2(97, -52), glm::vec2(0, 0), 10.f, 8, glm::vec4(0, 0, 0, 1));
	// Blue
	Sphere* ball5 = new Sphere(glm::vec2(-97, -52), glm::vec2(0, 0), 10.f, 8, glm::vec4(0, 0, 0, 1));
	// White
	Sphere* ball6 = new Sphere(glm::vec2(-97, 52), glm::vec2(0, 0), 10.f, 8, glm::vec4(0, 0, 0, 1));

	ball1->SetKinematic(1);
	ball2->SetKinematic(1);
	ball3->SetKinematic(1);
	ball4->SetKinematic(1);
	ball5->SetKinematic(1);
	ball6->SetKinematic(1);

	ball1->SetTrigger(1);
	ball2->SetTrigger(1);
	ball3->SetTrigger(1);
	ball4->SetTrigger(1);
	ball5->SetTrigger(1);
	ball6->SetTrigger(1);



	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(ball3);
	m_physicsScene->AddActor(ball4);
	m_physicsScene->AddActor(ball5);
	m_physicsScene->AddActor(ball6);

	ball1->triggerEnter = [=](PhysicsObject* other)
	{
		std::cout << "Entered: " << other << std::endl;
		if (other == whiteBall)
		{
			whiteBall->SetPosition({ 0, 0 });
			whiteBall->SetVelocity({ 0, 0 });

		}
	};

	ball1->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

	ball2->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	ball2->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

	ball3->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	ball3->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

	ball4->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	ball4->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

	ball5->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	ball5->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

	ball6->triggerEnter = [=](PhysicsObject* other) {std::cout << "Entered: " << other << std::endl; };
	ball6->triggerExit = [=](PhysicsObject* other) {std::cout << "Exited: " << other << std::endl; };

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
	worldPos.x -= getWindowWidth() / 2;
	worldPos.y -= getWindowHeight() / 2;

	// Scale this according to the extents
	worldPos.x *= 2.f * m_extents / getWindowWidth();
	worldPos.y *= 2.f * m_extents / (m_aspectRatio * getWindowHeight());



	return worldPos;
}

void PhysicsProjectApp::AimAndShoot(aie::Input* a_input)
{


	if (a_input->isMouseButtonDown(0))
	{
		int xScreen, yScreen;
		a_input->getMouseXY(&xScreen, &yScreen);
		worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		aie::Gizmos::add2DCircle(worldPos, 5, 32, glm::vec4(0.3));
		aie::Gizmos::add2DLine(whiteBall->GetPosition(), worldPos, glm::vec4(1));

	}
	if (a_input->wasMouseButtonReleased(0))
	{
		whiteBall->ApplyForce((worldPos - whiteBall->GetPosition()), glm::vec2(0));
		std::cout << "hi" << std::endl;
	}
}

void PhysicsProjectApp::AddBallsToList(Sphere* a_ball)
{
	ballList.push_back(a_ball);
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
