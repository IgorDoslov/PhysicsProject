#include "PhysicsProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "glm\ext.hpp"
#include <Gizmos.h>
#include "Plane.h"
#include "PhysicsScene.h"
#include <vector>
//#include "Sphere.h"

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

	m_physicsScene->SetGravity(glm::vec2(0, -10));

	// Lower the value, the more accurate the simulation will be;
	// but it will increase the processing time required. If it
	// is too high it cause the sim to stutter and reduce stability.

	m_physicsScene->SetTimeStep(0.01f);

	//Sphere* ball;
	ball = new Sphere(glm::vec2(0, 10), glm::vec2(0, 1), 10.f, 10, glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(ball);

	Sphere* anotherBall;
	anotherBall = new Sphere(glm::vec2(0, 50), glm::vec2(0, 0), 3.f, 1, glm::vec4(0, 1, 0, 1));
	m_physicsScene->AddActor(anotherBall);

	Sphere* ball2;
	ball2 = new Sphere(glm::vec2(0, 60), glm::vec2(0, 1), 3.f, 1, glm::vec4(1, 0, 1, 1));
	m_physicsScene->AddActor(ball2);

	ball2->ApplyForce(glm::vec2(0, -30));
	anotherBall->ApplyForce(glm::vec2(0, -30));


	Plane* plane;
	plane = new Plane();
	m_physicsScene->AddActor(plane);

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