/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	EventManager.h
Purpose:	Contains the declaration for the Contacts class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_contactsh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Components\Body.h"

#pragma once
class Contacts
{
public:
	//Needs to be made by Colls manager
	Contacts();
	~Contacts();

	//bodies in contact with each other.
	Body* bodies[2];
};

