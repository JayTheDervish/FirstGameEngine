/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Sprite.h
Purpose:	Contains the definition for the Sprite class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_spritecpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#include "Sprite.h"

Sprite::Sprite(SDL_Surface * sprite)
{
	surface = sprite;
}

Sprite::~Sprite()
{
}

void Sprite::Initialize(GameObject * parent)
{
	//this->Transform = GetOwner()->has(Transform);
	daddy = parent;
}

void Sprite::Update(float dt)
{
}
