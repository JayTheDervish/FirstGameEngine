/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Controller.h
Purpose:	Contains the declaration for the Controller class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_controllerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include "..\InputManager.h"
#include "Transform.h"
#include "..\GameObjectManager.h"

#ifndef CONTROLLER_H
#define	CONTROLLER_H

extern InputManager * inputManager;

extern GameObjectManager * goManager;

class GameObject;

class Controller : public Component
{
public:
	Controller();
	~Controller();

	void Initialize(GameObject * parent);

	void Update(float dt);

	void Serialize(nlohmann::json j);

	void HandleEvents(EventType events);

	GameObject * GetOwner();

private:
	GameObject * daddy;
};

#endif // !CONTROLLER_H
