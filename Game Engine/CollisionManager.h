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


class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	std::list</*Contacts*/int *> contacts;
};

#endif // !CollisionManager_h