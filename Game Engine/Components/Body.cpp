/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Body.h
Purpose:	Contains the definition for the Body class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_bodycpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Body.h"

Body::Body()
{
}

Body::~Body()
{
}

void Body::Integrate(float gravity, float dt)
{
	mPrevPosX = mPosX;
	mPrevPosY = mPosY;

	totalForceY += gravity;
	mAccelX = totalForceX * invMass;
	mAccelY = totalForceY * invMass;

	mVelX = mAccelX * dt + mVelX;
	mVelY = mAccelY * dt + mVelY;

	mPosX = mVelX * dt + mPosX;
	mPosY = mVelY * dt + mPosY;

	totalForceX = totalForceY = 0.0f;

	Transform * transfrom = (Transform *)daddy->getComponent(TRANSFORM);
	transfrom->postion2d.x = mPosX;
	transfrom->postion2d.y = mPosY;
}

void Body::Update(float dt)
{
}

void Body::Initialize(GameObject * parent)
{
	daddy = parent;
	Transform * transfrom = (Transform *)daddy->getComponent(TRANSFORM);

	mPosX = mPrevPosX = transfrom->postion2d.x;
	mPosY = mPrevPosY = transfrom->postion2d.y;
}

void Body::Serialize(nlohmann::json j)
{
}

GameObject * Body::GetOwner()
{
	return daddy;
}
