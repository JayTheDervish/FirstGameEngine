/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObject.cpp
Purpose:	Contains the implementation of the GameObject class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_gameobjectcpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/


#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
	//loop through all components and delete them.
	for (std::map<COMPONENTS, Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		delete it->second;
	}

	//clear map
	components.clear();

}

void GameObject::Update(float dt)
{
	//loop through all components and update them
	for (std::map<COMPONENTS, Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		it->second->Update(dt);
	}

}

Component * GameObject::getComponent(COMPONENTS component)
{
	std::map<COMPONENTS, Component*>::iterator it;
	it = components.find(component);
	if (it != components.end())
		return it->second;
	return NULL;
}

void GameObject::AddComponent(COMPONENTS type, Component * component)
{
	components.insert(std::pair<COMPONENTS, Component*>(type, component) );
}

void GameObject::HandleEvent()
{

}
