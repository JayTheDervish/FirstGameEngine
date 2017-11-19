/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Body.h
Purpose:	Contains the declaration for the Body class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_bodyh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once

#ifndef Body_h
#define Body_h

#include "Component.h"
#include "GameObject.h"
#include "..\Shapes.h"

class GameObject;

class Body : public Component
{
public:
	Body();
	~Body();

	float mPosX, mPosY;
	float mPrevPosX, mPrevPosY;
	float mVelX, mVelY;
	float mAccelX, mAccelY;
	float totalForceX, totalForceY;
	float mass, invMass;

	void Integrate(float gravity, float dt);

	void Update(float dt);

	void Initialize(GameObject * parent);

	void Serialize(nlohmann::json j);

	GameObject * GetOwner();

private:
	GameObject * daddy;

	Shape * shape;
};
#endif // !Body_h
