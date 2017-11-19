#include "Shapes.h"

Shape::Shape(SHAPE_TYPE type)
{
}

Body * Shape::getOwner()
{
	return owner;
}
