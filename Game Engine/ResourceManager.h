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
#include "MathLibraries\Vector2D.h"
#include <vector>

class ResourceManager
{
public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface * getSprite(char type);


	//Will move to Renderer when it is implemented.
	void Draw(SDL_Surface * windowSurface, SDL_Rect * players[], std::vector<Vector2D> positions);
	static ResourceManager* resources;
private:
	SDL_Surface * surfaces[3]; 

};

#endif // !RESOURCEMANAGER_H
