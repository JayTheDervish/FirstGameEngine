/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	GameObjectFactory.cpp
Purpose:	Contains the definition for the GameObjectFactory class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_GameObjectFactorycpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 11/2/2017

- End Header --------------------------------------------------------*/

#include "GameObjectFactory.h"

GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject * GameObjectFactory::CreateObject(nlohmann::json j)
{
	GameObject * newObj = new GameObject();

	
	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
		std::cout << it.key() << " : " << it.value() << "\n";
	}

	//Archetype serialization
	if (!j["Player.json"].is_null())
	{
		newObj->gameObjectID = "Player";

		std::ifstream inputfile("Resources/Player.json");
		nlohmann::json o;
		inputfile >> o;

		//Go through Components array and serialize components
		for (int i = 0; i < o["Components"].size(); ++i)
		{
			nlohmann::json component = o["Components"][i];
			if (!component["Transform"].is_null())
			{
				nlohmann::json playertransform = j["Player.json"];

				nlohmann::json trans = playertransform["Transform"];

				int x = trans["x"];
				int y = trans["y"];

				Transform * transform = new Transform(x, y);
				transform->Initialize(newObj);
				newObj->AddComponent(TRANSFORM, transform);
			}
			else if (!component["Sprite"].is_null())
			{
				std::string spriteIcon = component["Sprite"];

				Sprite * sprite = new Sprite(resources.getSprite(spriteIcon[0]));
				sprite->Initialize(newObj);
				newObj->AddComponent(SPRITE, sprite);
			}
			else if (!component["Controller"].is_null())
			{
				Controller * controller = new Controller();
				controller->Initialize(newObj);
				newObj->AddComponent(CONTROLLER, controller);
			}
		}
	}
	if (!j["Enemy.json"].is_null())
	{
		newObj->gameObjectID = "Enemy";

		std::ifstream inputfile("Resources/Enemy.json");
		nlohmann::json o;
		inputfile >> o;

		//Go through Components array and serialize components
		for (int i = 0; i < o["Components"].size(); ++i)
		{
			nlohmann::json component = o["Components"][i];
			if (!component["Transform"].is_null())
			{
				nlohmann::json enemytransform = j["Enemy.json"];

				nlohmann::json trans = enemytransform["Transform"];

				int x = trans["x"];
				int y = trans["y"];

				Transform * transform = new Transform(x, y);
				transform->Initialize(newObj);
				newObj->AddComponent(TRANSFORM, transform);
			}
			else if (!component["Sprite"].is_null())
			{
				std::string spriteIcon = component["Sprite"];

				Sprite * sprite = new Sprite(resources.getSprite(spriteIcon[0]));
				sprite->Initialize(newObj);
				newObj->AddComponent(SPRITE, sprite);
			}
			else if (!component["UpDown"].is_null())
			{
				UpDown * updown = new UpDown();
				updown->Initialize(newObj);
				newObj->AddComponent(UPDOWN, updown);
			}
		}
	}
	/*if (!j["Wall1.json"].is_null())
	{
		std::ifstream inputfile("Resources/Enemy.json");
		nlohmann::json o;
		inputfile >> o;

		//Go through Components array and serialize components
		for (int i = 0; i < o["Components"].size(); ++i)
		{
			o["Components"][i];
		}
	}*/

	//return object for initialization
	return newObj;
}
