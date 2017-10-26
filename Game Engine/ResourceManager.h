/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	ResourceManager.h
Purpose:	Contains the declaration of the ResourceManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_resourcemanagerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#pragma once

#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL_surface.h>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	SDL_Rect * getSprite(int player);

	void Draw(SDL_Surface * windowSurface, SDL_Rect * players[2]);
private:
	SDL_Surface * Volts[2]; //Will change as needed (Name included)
};

#endif // !RESOURCEMANAGER_H
