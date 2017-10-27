/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Sprite.h
Purpose:	Contains the declaration for the Sprite class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_maincpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/


#ifndef Sprite_H
#define Sprite_H

#include <SDL_surface.h>
#include "GameObject.h"
#include "Transform.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void Initialize(GameObject* parent);

	void Update();

	SDL_Surface * surface;

private:
};

#endif // !Sprite_H


#pragma once
