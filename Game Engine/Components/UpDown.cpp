/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	UpDown.cpp
Purpose:	Contains the definition for the UpDown class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_updowncpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "UpDown.h"
#include "GameObject.h"
#include "Body.h"
#include "Transform.h"
#include "..\json.hpp"
#include "..\GameObjectManager.h"

UpDown::UpDown(bool special)
{
	_special = special;
}

UpDown::~UpDown()
{
}

void UpDown::Initialize(GameObject * parent)
{
	daddy = parent;
	elapsedTime = 0.0f;
}

int fps = 0;
void UpDown::Update(float dt)
{
	Body * body = static_cast<Body*>(daddy->getComponent(BODY));
	Transform * transform = (Transform *)daddy->getComponent(TRANSFORM);


	if (++fps%60==0 && _special)
	{

		std::ifstream inputfile("Resources/Bullet.json");
		nlohmann::json o;
		inputfile >> o;

		GameObject* pGO = GameObjectManager::goManager->CreateObject(o);

		Transform* pTransform = static_cast<Transform*>(pGO->getComponent(TRANSFORM));



		Body* pBody = static_cast<Body*>(pGO->getComponent(BODY));

		pBody->mPrevPosX = pBody->mPosX = pTransform->postion2d.x = transform->postion2d.x + 0.1 * cosf(transform->angle);
		pBody->mPrevPosX = pBody->mPosY = pTransform->postion2d.y = transform->postion2d.y + 0.1 * sinf(transform->angle);

		pTransform->angle = transform->angle;

		pBody->mVelX = body->mVelX + 100 * dt * cosf(pTransform->angle);
		pBody->mVelY = body->mVelY + 100 * dt * sinf(pTransform->angle);


		GameObjectManager::goManager->spawns.push_back(pGO);
	}

	transform->angle += 0.1*dt;

	if (elapsedTime > 0.0f && elapsedTime < 5.0f)
	{
		body->mVelY -= 0.01*dt * sinf(transform->angle);
		body->mVelX += 0.01*dt * cosf(transform->angle);
	}
	else if (elapsedTime > 5.0f && elapsedTime < 10.0f)
	{
		body->mVelY += 0.01*dt * sinf(transform->angle);
		body->mVelX -= 0.01*dt * cosf(transform->angle);
	}

	elapsedTime = elapsedTime + dt;
	if (elapsedTime >= 10.0f)
		elapsedTime = 0.0f;
}

void UpDown::Serialize(nlohmann::json j)
{
}

void UpDown::HandleEvents(EventType events)
{
}

GameObject * UpDown::GetOwner()
{
	return daddy;
}
