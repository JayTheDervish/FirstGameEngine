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

UpDown::UpDown()
{
}

UpDown::~UpDown()
{
}

void UpDown::Initialize(GameObject * parent)
{
	daddy = parent;
	elapsedTime = 0.0f;
}


void UpDown::Update(float dt)
{
	Transform * transform = (Transform *)daddy->getComponent(TRANSFORM);

	if (elapsedTime > 0.0f && elapsedTime < 5.0f)
	{
		transform->postion2d.y -= 1;
		transform->postion2d.x += 1;
	}
	else if (elapsedTime > 5.0f && elapsedTime < 10.0f)
	{
		transform->postion2d.y += 1;
		transform->postion2d.x -= 1;
	}

	elapsedTime = elapsedTime + dt;
	if (elapsedTime >= 10.0f)
		elapsedTime = 0.0f;
}

void UpDown::Serialize(nlohmann::json j)
{
}

GameObject * UpDown::GetOwner()
{
	return daddy;
}
