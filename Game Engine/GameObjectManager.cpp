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

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (std::vector<GameObject *>::iterator it = objects.begin(); it != objects.end(); ++it) {
		delete *it;
	}
}

void GameObjectManager::Load(nlohmann::json filename)
{
	nlohmann::json j; //Objects
	nlohmann::json k; //Player.json
	nlohmann::json l; //Transform
	nlohmann::json m; //position2D
	for (nlohmann::json::iterator it = filename.begin(); it != filename.end(); ++it) {
		 j = filename[it.key()][0];
		std::cout << it.key() << " : " << it.value() << "\n";
	}

	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
		k = j[it.key()];
		std::cout << it.key() << " : " << it.value() << "\n";
	}

	for (nlohmann::json::iterator it = k.begin(); it != k.end(); ++it) {
		l = k[it.key()];
		std::cout << it.key() << " : " << it.value() << "\n";
	}

	for (nlohmann::json::iterator it = l.begin(); it != l.end(); ++it) {
		m = l[it.key()];
		std::cout << it.key() << " : " << it.value() << "\n";
	}
}
