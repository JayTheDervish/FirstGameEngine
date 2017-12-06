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

Controller::Controller()
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
	inputManager->Update();

	Transform * transform = (Transform *)daddy->getComponent(TRANSFORM);

	if (inputManager->isP1DownPressed())
		transform->postion2d.y += -1*dt;
	if (inputManager->isP1UpPressed())
		transform->postion2d.y += 1*dt;
	if (inputManager->isP1RightPressed())
		transform->postion2d.x += 1*dt;
	if (inputManager->isP1LeftPressed())
		transform->postion2d.x += -1 * dt;

	if (inputManager->isRotateLeftPressed())
		transform->angle += 1 * dt;
	if (inputManager->isRotateRightPressed())
		transform->angle += -1 * dt;

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

	if (inputManager->isP1Action1Pressed())
	{
		nlohmann::json j = { "bullet",{
			{ "Transform", 
				{ "x", static_cast<Transform*>(daddy->getComponent(TRANSFORM))->postion2d.x },
				{ "y", static_cast<Transform*>(daddy->getComponent(TRANSFORM))->postion2d.y },
				{ "scale", 0.01 }
			} 
		} };

		goManager->CreateObject(j);

		printf("Player 1 Action Button 1 is pressed.\n");
	}
	if (inputManager->isP1Action1Triggered())
		printf("Player 1 Action Button 1 is triggered.\n");
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
