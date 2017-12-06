/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Controller.h
Purpose:	Contains the definition for the PhysicsManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_physicsmanagercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "PhysicsManager.h"


PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Update(float dt)
{
	for (auto gameObject : goManager->objects)
	{
		Body* pBody = static_cast<Body*>(gameObject->getComponent(BODY));
		if (pBody)
		{
			//pBody->Integrate(0, dt);
		}
	}
}
