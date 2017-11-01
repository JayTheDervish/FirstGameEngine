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
#include "..\MathLibraries\Vector2D.h"

#ifndef TRANSFORM_H
#define TRANSFORM_H

class Transform : public Component
{
public:
	Transform();
	~Transform();

	void Update();

	Vector2D postion2d;


	//Get rid of this
	int P1Xpos, P1Ypos, P2Xpos, P2Ypos;

private:
};

#endif // !TRANSFORM_H



