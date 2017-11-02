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
	if (transform) { delete transform; }
	if (sprite) { delete sprite; }
}

void GameObject::Update()
{
}
