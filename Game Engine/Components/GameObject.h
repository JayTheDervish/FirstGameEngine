/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObject.h
Purpose:	Contains the declaration of the GameObject class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_gameobjecth
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/
#pragma once

#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "UpDown.h"
#include "Body.h"
#include "Component.h"
#include "..\EventManager.h" //I do not like this include
#include <map>
#include <string>

#ifndef GameObject_H
#define GameObject_H

class GameObject
{
public:
	GameObject();
	~GameObject();

	//Calls Updates for each Compoenent
	void Update(float dt);

	//GameObect ID
	std::string gameObjectID;

	//Allows access to other components
	Component * getComponent(COMPONENTS component);

	//Add Components
	void AddComponent(COMPONENTS type, Component* component);

	//Method to Handle events
	void HandleEvent(EventType type);

	//map with all components
	std::map<COMPONENTS, Component*> components;


private:
	


};

#endif // !GameObject_H



