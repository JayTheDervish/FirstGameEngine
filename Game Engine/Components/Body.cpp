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
#include "GameObject.h"
#include "Transform.h"
#include "..\Circle.h"
#include "..\Box.h"

Body::Body()
{
}

Body::Body(SHAPE_TYPE shapeType)
{
	type = shapeType;
}

Body::~Body()
{
	delete shape;
}

void Body::Integrate(float dt)
{
	mPrevPosX = mPosX;
	mPrevPosY = mPosY;

	
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
	Transform * transform = (Transform *)daddy->getComponent(TRANSFORM);

	shape = new Shape(type);

	shape->Initialize(this);

	if (shape->shape == CIRCLE)
		static_cast<Circle *>(shape)->radius = transform->scale.x * 0.5f;
	else
	{
		static_cast<Box *>(shape)->height = transform->scale.y * 0.5f;
		static_cast<Box *>(shape)->width = transform->scale.x * 0.5f;
	}

	mPosX = mPrevPosX = transform->postion2d.x;
	mPosY = mPrevPosY = transform->postion2d.y;
}

void Body::Serialize(nlohmann::json j)
{
}

void Body::HandleEvents(EventType events)
{
}

GameObject * Body::GetOwner()
{
	return daddy;
}

Shape * Body::getShape()
{
	return shape;
}
