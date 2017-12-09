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
#include "Components\Transform.h"
#include "Components\Sprite.h"
#include "Components\Controller.h"
#include "Components\UpDown.h"
#include "Components\Body.h"
#include "Components\GameObject.h"
#include "ResourceManager.h"
#include "JsonReader.h"


GameObjectFactory::GameObjectFactory()
{
}

GameObjectFactory::~GameObjectFactory()
{
}

GameObject * GameObjectFactory::CreateObject(nlohmann::json j)
{
	GameObject * newObj = new GameObject();


	//Archetype serialization
	if (AcryJson::ValueExists(j, "Player.json"))
	{
		newObj->gameObjectID = "Player";

		std::ifstream inputfile("Resources/Player.json");
		nlohmann::json o;
		inputfile >> o;

		//Go through Components array and serialize components
		for (int i = 0; i < o["Components"].size(); ++i)
		{
			nlohmann::json component = o["Components"][i];
			if (AcryJson::ValueExists(component, "Transform") /*!component["Transform"].is_null()*/)
			{
				nlohmann::json playertransform = j["Player.json"];

				nlohmann::json trans = playertransform["Transform"];

				nlohmann::json scales = component["Transform"];

				float x = playertransform["Transform"]["x"];
				float y = playertransform["Transform"]["y"];
				float scaleVal = component["Transform"]["scale"];


				Vector2D scale;

				scale.x = scale.y = scaleVal;


				Transform * transform = new Transform(x, y, scale);
				transform->Initialize(newObj);
				newObj->AddComponent(TRANSFORM, transform);
			}
			else if (!component["Sprite"].is_null())
			{
				std::string spriteIcon = component["Sprite"];

				Sprite * sprite = new Sprite(ResourceManager::resources->getSprite(spriteIcon[0]));
				sprite->Initialize(newObj);
				newObj->AddComponent(SPRITE, sprite);
			}
			else if (!component["Controller"].is_null())
			{
				std::string bullet;
				bullet = component.at("Bullet").get<std::string>();
				Controller * controller = new Controller(bullet);
				controller->Initialize(newObj);
				newObj->AddComponent(CONTROLLER, controller);
			}
			else if (!component["Body"].is_null())
			{
				Body * body = new Body();
				body->Initialize(newObj);
				newObj->AddComponent(BODY, body);
			}
		}
	}



	if (AcryJson::ValueExists(j, "Enemy.json"))
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

				nlohmann::json scales = component["Transform"]["scale"];

				float x = trans["x"];
				float y = trans["y"];

				float scaleVal = component["Transform"]["scale"];

				Vector2D scale;

				scale.x = scale.y = scaleVal;

				Transform * transform = new Transform(x, y, scale);
				transform->Initialize(newObj);
				newObj->AddComponent(TRANSFORM, transform);
			}
			else if (!component["Sprite"].is_null())
			{
				std::string spriteIcon = component["Sprite"];

				Sprite * sprite = new Sprite(ResourceManager::resources->getSprite(spriteIcon[0]));
				sprite->Initialize(newObj);
				newObj->AddComponent(SPRITE, sprite);
			}
			else if (!component["UpDown"].is_null())
			{
				UpDown * updown = new UpDown();
				updown->Initialize(newObj);
				newObj->AddComponent(UPDOWN, updown);
			}
			else if (!component["Body"].is_null())
			{
				Body * body = new Body();
				body->Initialize(newObj);
				newObj->AddComponent(BODY, body);
			}
		}
	}



	if (AcryJson::ValueExists(j, "Wall1.json"))
	{
		newObj->gameObjectID = "Wall1";

		std::ifstream inputfile("Resources/Wall1.json");
		nlohmann::json o;
		inputfile >> o;

		//Go through Components array and serialize components
		for (int i = 0; i < o["Components"].size(); ++i)
		{
			o["Components"][i];
			nlohmann::json component = o["Components"][i];
			if (!component["Transform"].is_null())
			{
				nlohmann::json walltransform = j["Wall1.json"];

				nlohmann::json trans = walltransform["Transform"];

				nlohmann::json scales = component["Transform"]["scale"];

				float x = trans["x"];
				float y = trans["y"];

				Vector2D scale;

				scale.x = component["Transform"]["scale"]["x"];
				scale.y = component["Transform"]["scale"]["y"];

				Transform * transform = new Transform(x, y, scale);
				transform->Initialize(newObj);
				newObj->AddComponent(TRANSFORM, transform);
			}
			else if (!component["Sprite"].is_null())
			{
				std::string spriteIcon = component["Sprite"];

				Sprite * sprite = new Sprite(ResourceManager::resources->getSprite(spriteIcon[0]));
				sprite->Initialize(newObj);
				newObj->AddComponent(SPRITE, sprite);
			}
			else if (!component["Body"].is_null())
			{
				Body * body = new Body();
				body->Initialize(newObj);
				newObj->AddComponent(BODY, body);
			}
		}
	}


	if (AcryJson::ValueExists(j, "Wall2.json"))
	{
		newObj->gameObjectID = "Wall2";

		std::ifstream inputfile("Resources/Wall2.json");
		nlohmann::json o;
		inputfile >> o;

		//Go through Components array and serialize components
		for (int i = 0; i < o["Components"].size(); ++i)
		{
			o["Components"][i];
			nlohmann::json component = o["Components"][i];
			if (!component["Transform"].is_null())
			{
				nlohmann::json walltransform = j["Wall2.json"];

				nlohmann::json trans = walltransform["Transform"];

				nlohmann::json scales = component["Transform"]["scale"];

				float x = trans["x"];
				float y = trans["y"];

				Vector2D scale;

				scale.x = component["Transform"]["scale"]["x"];
				scale.y = component["Transform"]["scale"]["y"];

				Transform * transform = new Transform(x, y, scale);
				transform->Initialize(newObj);
				newObj->AddComponent(TRANSFORM, transform);
			}
			else if (!component["Sprite"].is_null())
			{
				std::string spriteIcon = component["Sprite"];

				Sprite * sprite = new Sprite(ResourceManager::resources->getSprite(spriteIcon[0]));
				sprite->Initialize(newObj);
				newObj->AddComponent(SPRITE, sprite);
			}
			else if (!component["Body"].is_null())
			{
				Body * body = new Body();
				body->Initialize(newObj);
				newObj->AddComponent(BODY, body);
			}
		}
	}

		//Create Bullet
		bool bullet = AcryJson::ValueExists(j, "bullet");
		if (bullet)
		{
			newObj->gameObjectID = "bullet";

			bool components = AcryJson::ValueExists(j["bullet"], "Components");

			if (components)
			{

				for (int i = 0; i < j["bullet"]["Components"].size(); ++i)
				{

					nlohmann::json component = j["bullet"]["Components"][i];

					if (!component["Transform"].is_null()/*AcryJson::ValueExists(j["Components"][i], "Transform")*/)
					{
						float x = component["Transform"]["x"];
						float y = component["Transform"]["y"];

						float scaleVal = component["Transform"]["scale"];

						Vector2D scale;

						scale.x = scale.y = scaleVal;

						Transform * transform = new Transform(x, y, scale);
						transform->Initialize(newObj);
						newObj->AddComponent(TRANSFORM, transform);
					}
					else if (!component["Sprite"].is_null()/*AcryJson::ValueExists(j["Components"][i], "Sprite")*/)
					{
						std::string spriteIcon = component["Sprite"];

						Sprite * sprite = new Sprite(ResourceManager::resources->getSprite(spriteIcon[0]));
						sprite->Initialize(newObj);
						newObj->AddComponent(SPRITE, sprite);
					}
					else if (!component["Body"].is_null()/*AcryJson::ValueExists(j["Components"][i], "Body")*/)
					{
						Body * body = new Body();
						body->Initialize(newObj);
						newObj->AddComponent(BODY, body);
					}
				}
			}
		}

		//return object for initialization
		return newObj;
	}

