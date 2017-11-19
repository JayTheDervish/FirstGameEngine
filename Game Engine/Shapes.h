#pragma once

#ifndef Shapes_h
#define Shapes_h

#include "Components\Body.h"

enum SHAPE_TYPE { CIRCLE, AABB, NUM };

class Shape
{
public:
	Shape(SHAPE_TYPE type);

	Body * getOwner();
	SHAPE_TYPE shape;

private:
	Body * owner;
};
#endif // !Shapes_h
