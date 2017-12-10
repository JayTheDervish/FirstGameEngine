/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Controller.cpp
Purpose:	Contains the definition for the Controller class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_controllercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Controller.h"
#include "GameObject.h"
#include "..\json.hpp"
#include "..\GameObjectManager.h"
#include "..\InputManager.h"
#include "Transform.h"
#include "Body.h"

extern InputManager* inputManager;


Controller::Controller(std::string _bullet): bullet(_bullet)
{

}

Controller::~Controller()
{
}

void Controller::Initialize(GameObject * parent)
{
	daddy = parent;
}

void Controller::Update(float dt)
{

#pragma region Input
	

	Body * body = (Body *)daddy->getComponent(BODY);
	Transform * transform = (Transform *)daddy->getComponent(TRANSFORM);

	if (inputManager->isP1DownPressed())
	{
		body->totalForceY += -1700 * dt * sinf(transform->angle);
		body->totalForceX += -1700 * dt  * cosf(transform->angle);
	}
	else
		body->mVelY = 0;
	if (inputManager->isP1UpPressed())
	{
		body->totalForceY += 1700 * dt * sinf(transform->angle);
		body->totalForceX += 1700 * dt * cosf(transform->angle);
	}
	else
		body->mVelY = 0;
	if (inputManager->isP1RightPressed())
		transform->angle += -1 * dt;
	else
		body->mVelX = 0;
	if (inputManager->isP1LeftPressed())
		transform->angle += 1 * dt;
	//	body->totalForceX += -1700 * dt  * cosf(transform->angle);
	else
		body->mVelX = 0;

	//if (inputManager->isRotateLeftPressed())
	//	transform->angle += 1 * dt;
	//if (inputManager->isRotateRightPressed())
	//	transform->angle += -1 * dt;

	/*
	if (inputManager.isP2DownPressed())
		players[1]->y += -1;
	if (inputManager.isP2UpPressed())
		players[1]->y += 1;
	if (inputManager.isP2RightPressed())
		players[1]->x += 1;
	if (inputManager.isP2LeftPressed())
		players[1]->x += -1;*/

	/*if (inputManager->isP1Action2Released())
		printf("Player 1 Action Button 2 is released.\n");*/

	if (inputManager->isP1Action1Triggered())
	{

		std::ifstream inputfile("Resources/Bullet.json");
		nlohmann::json o;
		inputfile >> o;

		GameObject* pGO = GameObjectManager::goManager->CreateObject(o);

		Transform* pTransform = static_cast<Transform*>(pGO->getComponent(TRANSFORM));
		
		

		Body* pBody = static_cast<Body*>(pGO->getComponent(BODY));

		pBody->mPrevPosX = pBody->mPosX = pTransform->postion2d.x = transform->postion2d.x;
		pBody->mPrevPosX = pBody->mPosY = pTransform->postion2d.y = transform->postion2d.y;

		pTransform->angle = transform->angle;

		pBody->mVelX = body->mVelX + 100*dt * cosf(pTransform->angle);
		pBody->mVelY = body->mVelY + 100*dt * sinf(pTransform->angle);


		GameObjectManager::goManager->spawns.push_back(pGO);
	}
//	if (inputManager->isP1Action1Triggered())
//		printf("Player 1 Action Button 1 is triggered.\n");
	if (inputManager->isP1Action1Released())
		printf("Player 1 Action Button 1 is released.\n");
	if (inputManager->isP1Action2Pressed())
		printf("Player 1 Action Button 2 is pressed.\n");
	if (inputManager->isP1Action2Released())
		printf("Player 1 Action Button 2 is released.\n");
	if (inputManager->isP1Action2Triggered())
		printf("Player 1 Action Button 2 is triggered.\n");


	/*
	if (inputManager.isP2Action1Pressed())
		printf("Player 2 Action Button 1 is pressed.\n");
	if (inputManager.isP2Action1Triggered())
		printf("Player 2 Action Button 1 is triggered.\n");
	if (inputManager.isP2Action1Released())
		printf("Player 2 Action Button 1 is released.\n");
	if (inputManager.isP2Action2Pressed())
		printf("Player 2 Action Button 2 is pressed.\n");
	if (inputManager.isP2Action2Released())
		printf("Player 2 Action Button 2 is released.\n");
	if (inputManager.isP2Action2Triggered())
		printf("Player 2 Action Button 2 is triggered.\n");*/



#pragma endregion Input

}

void Controller::Serialize(nlohmann::json j)
{
}

void Controller::HandleEvents(EventType events)
{
}

GameObject * Controller::GetOwner()
{
	return daddy;
}
