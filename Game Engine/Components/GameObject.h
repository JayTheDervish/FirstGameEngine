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


#include "Sprite.h"
#include "Transform.h"
#include "Component.h"
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
	void Update();


	//map with all components
	std::map<std::string, Component*> components;

	//delete these
	Transform *transform;
	Sprite *sprite;

private:
	


};

#endif // !GameObject_H


#pragma once
