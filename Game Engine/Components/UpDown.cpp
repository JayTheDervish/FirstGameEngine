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

UpDown::UpDown()
{
}

UpDown::~UpDown()
{
}

void UpDown::Initialize(GameObject * parent)
{
	daddy = parent;
}

void UpDown::Update()
{
	if (daddy->transform->postion2d.y > 0)
		daddy->transform->postion2d.y -= 1;
	else
		daddy->transform->postion2d.y += 1;
}
