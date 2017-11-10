/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	UpDown.h
Purpose:	Contains the declaration for the UpDown class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_updownh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"

#ifndef UPDOWN_H
#define UPDOWN_H

class GameObject;

class UpDown : public Component
{
public:
	UpDown();
	~UpDown();

	void Initialize(GameObject * parent);

	void Update(float dt);

	void Serialize(FILE **fpp);
	GameObject * GetOwner();
private:
	GameObject * daddy;
	float elapsedTime;
};

#endif