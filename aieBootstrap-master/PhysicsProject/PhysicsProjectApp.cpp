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
	DrawRect();
	SphereAndPlane();



	/*Plane* plane2;
	plane2 = new Plane();
	m_physicsScene->m_particles.push_back(plane2);*/

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

	/*if (input->isKeyDown(aie::INPUT_KEY_SPACE))
	{
		ball->ApplyForce({ 0,100 });
	}*/



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

	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100 / aspectRatio, 100 / aspectRatio, -1.f, 1.f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}

void PhysicsProjectApp::SetupContinuousDemo(glm::vec2 startPos, float inclination, float speed, float gravity)
{
	float t = 0.0f;
	float tStep = 0.1f;
	float radius = 1.0f;
	int segments = 12;

	glm::vec4 colour = glm::vec4(1, 1, 0, 1);
	glm::vec2 pos;


	while (t <= 5)
	{
		// calculate the x, y position of the projectile at time t

		startPos.x = speed * glm::cos(0.78) * t;
		startPos.y = speed * glm::sin(0.78) * t - 0.5 * gravity * (t * t);




		aie::Gizmos::add2DCircle(startPos, radius, segments, colour);
		t += tStep;
	}
}

void PhysicsProjectApp::DrawRect()
{
	m_physicsScene->AddActor(new Sphere(glm::vec2(20, 10), glm::vec2(-10, -17),
		1, 3, glm::vec4(1, 0, 0, 0)));
	m_physicsScene->AddActor(new Plane(glm::vec2(-0.65, 0.75), -1));

	Box* box1 = new Box(glm::vec2(-20, 0), glm::vec2(25, -4), 1, 4, 8, 4,
		glm::vec4(1, 1, 0, 1));

	box1->SetRotation(0.5);

	m_physicsScene->AddActor(box1);
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



	ball->ApplyForce(glm::vec2(80, 0), glm::vec2(0));
	anotherBall->ApplyForce(glm::vec2(-80, 0), glm::vec2(0));
	ball2->ApplyForce(glm::vec2(2, -30), glm::vec2(0));



	Plane* plane;
	plane = new Plane({ 0,1 }, 0.f);
	m_physicsScene->AddActor(plane);
}
