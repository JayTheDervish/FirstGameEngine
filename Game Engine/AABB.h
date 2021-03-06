/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	AABB.h
Purpose:	Contains the declaration for the AABB class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_aabbh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once

#include "Shapes.h"

#ifndef  AABB_h
#define AABB_h



class AABB :
	public Shape
{
public:
	AABB();
	~AABB();

	float height, width;
};

#endif // ! AABB_h