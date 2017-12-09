/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Main.cpp
Purpose:	Contains the declaration for the Transform class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_transformh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include "..\MathLibraries\Matrix2D.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

class GameObject;

class Transform : public Component
{
public:
	Transform(float x, float y, Vector2D scale);
	~Transform();

	void Initialize(GameObject * parent);
	void Update(float dt);

	Vector2D postion2d;
	Vector2D scale;
	float angle;
	Matrix2D modelingMatrix;
	bool skin;

	void Serialize(nlohmann::json j);

	void HandleEvents(EventType events);

	GameObject * GetOwner();

private:
	GameObject * daddy;
};

#endif // !TRANSFORM_H



