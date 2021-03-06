/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Body.h
Purpose:	Contains the definition for the Shapes class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_shapescpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Shapes.h"

Shape::Shape(SHAPE_TYPE type = CIRCLE)
{
	shape = type;
}

Shape::~Shape()
{
}

void Shape::Initialize(Body * parent)
{
	owner = parent;
}

Body * Shape::getOwner()
{
	return owner;
}
