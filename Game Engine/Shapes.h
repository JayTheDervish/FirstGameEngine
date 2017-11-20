/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Body.h
Purpose:	Contains the declaration for the Shapes class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_shapesh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once


#include "Components\Body.h"

#ifndef Shapes_h
#define Shapes_h

enum SHAPE_TYPE { CIRCLE, AABB, NUM };

class Body;

class Shape
{
public:
	Shape() {}
	Shape(SHAPE_TYPE type);

	virtual ~Shape();
	virtual void Initialize(Body * parent);
	virtual Body * getOwner();

	SHAPE_TYPE shape;

private:
	Body * owner;
};
#endif // !Shapes_h
