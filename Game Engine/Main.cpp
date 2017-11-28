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
#include <gl\glew.h>
#include <gl\freeglut.h>
#include "stdio.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "FrameRateController.h"
#include "GameObjectManager.h"
#include "MathLibraries\Vector2D.h"
#include <SDL_surface.h>
#include <Windows.h>
#include <vector>
#include <fstream>
#include "json.hpp"

FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

float FRAME_TIME_CAP = (1.0f / 60.0f) * 1000.0f;

InputManager * inputManager = new InputManager(1, 'j');
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

	//	SetConsoleTitle(L"Game Engine Console Input");
	}


	

	FrameRateController * frameRateController = new FrameRateController(FRAME_TIME_CAP);

	GameObjectManager * goManager = new GameObjectManager();

	std::ifstream inputfile("Resources/level.json");

	nlohmann::json j;

	

	inputfile >> j;
	

	//Load Level
	goManager->LoadLevel(j);


	// Game loop
#pragma region Game Loop
	while(true == appIsRunning)
	{
		

		float dt = frameRateController->getDeltaTime();
		
		//clearing the screen
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

		//Update all GameObjects
		goManager->UpdateAll(dt);

		//update screen buffer

		
		for (auto go : goManager->objects)
		{
			SDL_Rect * rect = new SDL_Rect();
			
			Transform * pTransform = (Transform *)go->getComponent(TRANSFORM);
			Sprite * pSprite = (Sprite *)go->getComponent(SPRITE);

			if (pTransform && pSprite) {
				rect->x = pTransform->postion2d.x;
				rect->y = pTransform->postion2d.y;

				rect->h = pSprite->surface->h;
				rect->w = pSprite->surface->w;

				SDL_BlitSurface(pSprite->surface, NULL, pWindowSurface, rect);
			}
		}


		//update screen
		SDL_UpdateWindowSurface(pWindow);

		//wait frames out
		frameRateController->WaitFrames();
		
	}
#pragma endregion Game Loop

	//Delete all GameObjects
	delete goManager;



	// Close if opened
	delete frameRateController;
	delete inputManager;

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}