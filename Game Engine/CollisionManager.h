/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObject.h
Purpose:	Contains the declaration of the CollisonManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_collisonmanagerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once
#ifndef CollisionManager_h
#define CollisionManager_h

#include <list>
#include "Shapes.h"
#include "MathLibraries\Vector2D.h"


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();


	//resets list of contacts after integration
	void reset();

	bool checkCollisionAndGenContacts(Shape shape1, Vector2D position1, Shape shape2, Vector2D position2);

	//Will be used to determine collision type
	typedef bool(*func)(Shape shape1, Vector2D position1, Shape shape2, Vector2D position);

	 bool CollisionArray[2][2];

	std::list</*Contacts*/int *> contacts;
};

#endif // !CollisionManager_h