/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObjectFactory.h
Purpose:	Contains the declaration for the GameObjectFactory class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_GameObjectFactoryh
Author:		Jay Coleman j.coleman 60000217
Creation date: 11/2/2017

- End Header --------------------------------------------------------*/

#pragma once
#include <string>
#include <fstream>
#include "json.hpp"

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H


class GameObject;
class GameObjectFactory
{
public:
	GameObjectFactory();
	~GameObjectFactory();

	GameObject * CreateObject(nlohmann::json j);
private:
};

#endif // !GAMEOBJECTFACTORY_H
