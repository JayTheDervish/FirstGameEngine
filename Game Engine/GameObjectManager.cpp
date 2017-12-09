/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObjectFactory.h
Purpose:	Contains the definition for the GameObjectManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_GameObjectManagercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 11/2/2017

- End Header --------------------------------------------------------*/

#include "GameObjectManager.h"

GameObjectManager* GameObjectManager::goManager = nullptr;

GameObjectManager::GameObjectManager()
{
	GOFactory = new GameObjectFactory();
}

GameObjectManager::~GameObjectManager()
{
	for (std::vector<GameObject *>::iterator it = objects.begin(); it != objects.end(); ++it) {
		delete *it;
	}
	objects.clear();
	delete GOFactory;
}


//Loads level from Json File
void GameObjectManager::LoadLevel(nlohmann::json filename)
{
	nlohmann::json o; //Objects
	for (nlohmann::json::iterator it = filename.begin(); it != filename.end(); ++it) {
		for (int i = 0; i < filename[it.key()].size() ; ++i)
		{
			o = filename[it.key()][i];
			objects.push_back(GOFactory->CreateObject(o));
		}
	}

}


//Calls every Object's Update method
void GameObjectManager::UpdateAll(float dt)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		objects[i]->Update(dt);
		if (!objects[i]->alive)
			graveyard.push_back(objects[i]);
	}

	KillDead();

	//Spawn new objects
	for (int i = 0; i < spawns.size(); ++i)
		objects.push_back(spawns[i]);
	spawns.clear();
}

void GameObjectManager::KillDead()
{
	for (auto objPointer : graveyard)
		objects.erase(std::remove(objects.begin(), objects.end(), objPointer), objects.end());
	graveyard.clear();
}


//Can create an object during gameplay.
 GameObject* GameObjectManager::CreateObject(nlohmann::json j)
{
	return GOFactory->CreateObject(j);
}
