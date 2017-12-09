/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Transform.cpp
Purpose:	Contains the definition for the Transform class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_transformcpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Transform.h"

Transform::Transform(float  x, float y, Vector2D scale)
{
	postion2d.x = x;
	postion2d.y = y;

	scale = scale;

	skin = false;
}

Transform::~Transform()
{
}

void Transform::Initialize(GameObject * parent)
{
	daddy = parent;
}

void Transform::Update(float dt)
{
	Matrix2D translate;
	Matrix2D rotation;
	Matrix2D scaleMat;

	Matrix2DTranslate(&translate, postion2d.x, postion2d.y);
	Matrix2DScale(&scaleMat, scale.x, scale.y);
	Matrix2DRotRad(&rotation, angle);

	Matrix2DConcat(&modelingMatrix, &rotation, &scaleMat);
	Matrix2DConcat(&modelingMatrix, &translate, &modelingMatrix);
}

void Transform::Serialize(nlohmann::json j)
{
}

void Transform::HandleEvents(EventType events)
{
}

GameObject * Transform::GetOwner()
{
	return daddy;
}
