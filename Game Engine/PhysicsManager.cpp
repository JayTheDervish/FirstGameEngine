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
#include "GameObjectManager.h"
#include "Components\GameObject.h"
#include "Components\Body.h"
#include "Components\Transform.h"

PhysicsManager::PhysicsManager()
{
	collisions = new CollisionManager();
}

PhysicsManager::~PhysicsManager()
{
	delete collisions;
}

void PhysicsManager::Update(float dt)
{
	for (auto gameObject : GameObjectManager::goManager->objects)
	{
		Body* pBody = static_cast<Body*>(gameObject->getComponent(BODY));
		if (pBody)
		{
			pBody->Integrate(dt);
		}
	}

	collisions->reset();


	//Loop through all game objects
	for (auto gameObject1 : GameObjectManager::goManager->objects)
	{
		//For each game object
		for (auto gameObject2 : GameObjectManager::goManager->objects)
		{
			if (gameObject1->gameObjectID == "bullet")
			{
				//Check to see if bullet hits an enemy
				if (gameObject2->gameObjectID == "Enemy")
				{
					Body * body1 = static_cast<Body*>(gameObject1->getComponent(BODY));
					Body * body2 = static_cast<Body*>(gameObject2->getComponent(BODY));
					if (!collisions->checkCollisionAndGenContacts(body1->getShape(), static_cast<Transform *>(gameObject1->getComponent(TRANSFORM))->postion2d, body2->getShape(), static_cast<Transform *>(gameObject2->getComponent(TRANSFORM))->postion2d))
						continue;
					else
					{
						gameObject1->alive = false;
						gameObject2->alive = false;
					}
				}
				//Check if wall for bouncing (in future code)
			}
			else if (gameObject1->gameObjectID == "Player")
			{
				//Check to see if Player collides with Enemy
				if (gameObject2->gameObjectID == "Enemy")
				{
					Body * body1 = static_cast<Body*>(gameObject1->getComponent(BODY));
					Body * body2 = static_cast<Body*>(gameObject2->getComponent(BODY));
					if (!collisions->checkCollisionAndGenContacts(body1->getShape(), static_cast<Transform *>(gameObject1->getComponent(TRANSFORM))->postion2d, body2->getShape(), static_cast<Transform *>(gameObject2->getComponent(TRANSFORM))->postion2d))
						continue;
					else
					{
						gameObject1->alive = false;
						printf("YOU GOT HIT\n");
						//Fire event to game over screen
					}
				}
				//Check if wall
				else if (gameObject2->gameObjectID == "Wall1")
				{
					Body * body1 = static_cast<Body*>(gameObject1->getComponent(BODY));
					Body * body2 = static_cast<Body*>(gameObject2->getComponent(BODY));

				}
			}
		}
	}


}
