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

ResourceManager::ResourceManager()
{

	Volts[0] = SDL_LoadBMP("Resources/Volt.bmp");
	Volts[1] = SDL_LoadBMP("Resources/VoltStormHelm.bmp");

}

ResourceManager::~ResourceManager()
{
	//Free surfaces
	SDL_FreeSurface(Volts[0]);
	SDL_FreeSurface(Volts[1]);
}

SDL_Rect * ResourceManager::getSprite(int player)
{
	return nullptr;
}

void ResourceManager::Draw(SDL_Surface * windowSurface, SDL_Rect * players[2])
{
	SDL_BlitSurface(Volts[0], NULL, windowSurface, players[0]);
	SDL_BlitSurface(Volts[1], NULL, windowSurface, players[1]);
}

