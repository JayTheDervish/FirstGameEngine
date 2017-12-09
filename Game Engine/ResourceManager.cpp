/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	ResourceManager.cpp
Purpose:	Contains the definition of the methods of the ResourceManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_resourcemanagercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#include "ResourceManager.h"


ResourceManager* ResourceManager::resources = nullptr;
ResourceManager::ResourceManager()
{

	surfaces[0] = SDL_LoadBMP("Resources/Volt.bmp");
	surfaces[1] = SDL_LoadBMP("Resources/VoltStormHelm.bmp");
	surfaces[2] = SDL_LoadBMP("Resources/voltprime.bmp");
	surfaces[3] = SDL_LoadBMP("Resources/GrineerProsecutor.bmp");
}

ResourceManager::~ResourceManager()
{
	//Free surfaces
	for (int i = 0; i < 4; ++i)
		SDL_FreeSurface(surfaces[i]);
	
}

SDL_Surface * ResourceManager::getSprite(char type)
{
	if (type == 'c')
		return surfaces[2];
	if (type == 'e')
		return surfaces[3];
	return nullptr;
}


//to be removed.
void ResourceManager::Draw(SDL_Surface * windowSurface, SDL_Rect * players[], std::vector<Vector2D> positions)
{
	for (int i = 0; i < positions.size(); ++i)
	{
		players[i]->x = positions[i].x;
		players[i]->y = positions[i].y;
	}


	SDL_BlitSurface(surfaces[2], NULL, windowSurface, players[0]);
	SDL_BlitSurface(surfaces[3], NULL, windowSurface, players[1]);
}

