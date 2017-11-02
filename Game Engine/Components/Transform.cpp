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

Transform::Transform(int x, int y)
{
	postion2d.x = x;
	postion2d.y = y;
}

Transform::~Transform()
{
}

void Transform::Update()
{
}
