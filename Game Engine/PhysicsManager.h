/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Controller.h
Purpose:	Contains the declaration for the PhysicsManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_physicsmanagerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once

#ifndef PhysicsManager_h
#define PhysicsManager_h

#include "CollisionManager.h"


class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void Update(float dt);

private:
	CollisionManager * collisions;
};

#endif // !PhysicsManager_h
