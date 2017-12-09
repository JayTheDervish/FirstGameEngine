/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObjectFactory.h
Purpose:	Contains the declaration for the GameObjectManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_GameObjectManagerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 11/2/2017

- End Header --------------------------------------------------------*/

#pragma once

#include "Components\GameObject.h"
#include <vector>
#include "json.hpp"
#include "GameObjectFactory.h"

#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

class GameObjectFactory;

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	std::vector<GameObject *> objects;

	std::vector<GameObject *> spawns;

	std::vector<GameObject *> graveyard;

	void LoadLevel(nlohmann::json filename);

	void UpdateAll(float dt);

	void KillDead();

	GameObject* CreateObject(nlohmann::json j);
	
	static GameObjectManager* goManager;
private:
	GameObjectFactory * GOFactory;
};

#endif // !GAMEOBJECTMANAGER_H
