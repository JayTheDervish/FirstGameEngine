/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObject.h
Purpose:	Contains the definition of the CollisionManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_CollisionManagercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "CollisionManager.h"



CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::reset()
{
	//clears contacts
	contacts.clear();
}

bool CollisionManager::checkCollisionAndGenContacts(Shape shape1, Vector2D position1, Shape shape2, Vector2D position2)
{


	return false;
}
