/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Sprite.h
Purpose:	Contains the declaration for the Component class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_componenth
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once
#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include "..\json.hpp"

enum COMPONENTS
{
	TRANSFORM,
	SPRITE,
	CONTROLLER,
	UPDOWN,
	BODY
};

class Component
{
public:
	virtual void Update(float dt) = 0;
	virtual void Serialize(nlohmann::json j) = 0;

	virtual GameObject * GetOwner() = 0;

private:
};

#endif // !COMPONENT_H

