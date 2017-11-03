/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Main.cpp
Purpose:	Contains the main game loop and game processing.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_maincpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#include <SDL.h>
#include "stdio.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "FrameRateController.h"
#include "Components\GameObject.h"
#include "Components\Sprite.h"
#include "Components\Transform.h"
#include <SDL_surface.h>
#include <Windows.h>


FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

float FRAME_TIME_CAP = (1.0f / 60.0f) * 1000.0f;

InputManager inputManager;
ResourceManager resources;

int main(int argc, char* args[])
{
	SDL_Window *pWindow;
	int error = 0;
	bool appIsRunning = true;

	// Initialize SDL
	if((error = SDL_Init( SDL_INIT_VIDEO )) < 0 )
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		return 1;
	}


	pWindow = SDL_CreateWindow("Game Engine Test",		// window title
		SDL_WINDOWPOS_UNDEFINED,					// initial x position
		SDL_WINDOWPOS_UNDEFINED,					// initial y position
		800,										// width, in pixels
		600,										// height, in pixels
		SDL_WINDOW_SHOWN);

	// Check that the window was successfully made
	if (NULL == pWindow)
	{
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}


	SDL_Surface * pWindowSurface = SDL_GetWindowSurface(pWindow);

	//To create the console
	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}


	SDL_Rect * players[2];

	players[0] = new SDL_Rect();

	players[0]->x = 0;
	players[0]->y = 0;
	players[0]->h = 175;
	players[0]->w = 280;

	players[1] = new SDL_Rect();

	players[1]->x = 300;
	players[1]->y = 0;
	players[1]->h = 160;
	players[1]->w = 256;

	FrameRateController * frameRateController = new FrameRateController(FRAME_TIME_CAP);

	//Creating game objects (one for each player/enemy)
	//Put in factory
	{
		//Player
		GameObject * object = new GameObject();
		object->transform = new Transform(0, 0);
		object->transform->Initialize(object);
		//240 x 180
		object->sprite = new Sprite(resources.getSprite('c'));
		object->sprite->Initialize(object);
		object->controller = new Controller();
		object->controller->Initialize(object);

		//Enemy
		GameObject * enemy = new GameObject();
		enemy->transform = new Transform(200, 200);
		enemy->transform->Initialize(enemy);
		//200 x 200
		enemy->sprite = new Sprite(resources.getSprite('e'));
		enemy->sprite->Initialize(enemy);
		enemy->updown = new UpDown();
		enemy->updown->Initialize(enemy);
	}
	

	// Game loop
#pragma region Game Loop
	while(true == appIsRunning)
	{
		

		float dt = frameRateController->getDeltaTime();
		
		SDL_FillRect(pWindowSurface, NULL, 0);


		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}

		}


		//update screen buffer
		resources.Draw(pWindowSurface, players);

		//update screen
		SDL_UpdateWindowSurface(pWindow);

		//wait frames out
		frameRateController->WaitFrames();
		
	}
#pragma endregion Game Loop



	// Close if opened
	delete frameRateController;

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}