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

	ResourceManager * resources = new ResourceManager();

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

	InputManager * inputManager = new InputManager(2, 'j');

	FrameRateController * frameRateController = new FrameRateController(FRAME_TIME_CAP);

	//Creating game objects (one for each player/enemy)
	//Put in factory
	{
		//Player
		GameObject *object = new GameObject();
		object->transform = new Transform(0, 0);
		object->sprite = new Sprite(resources->getSprite('c'));
		object->controller = new Controller();

		//Enemy
		GameObject * enemy = new GameObject();
		enemy->transform = new Transform(200, 200);
		enemy->sprite = new Sprite(resources->getSprite('e'));
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

#pragma region Input
		inputManager->Update();

		if (inputManager->isP1DownPressed())
			players[0]->y += -1;
		if (inputManager->isP1UpPressed())
			players[0]->y += 1;
		if (inputManager->isP1RightPressed())
			players[0]->x += 1;
		if (inputManager->isP1LeftPressed())
			players[0]->x += -1;
		if (inputManager->isP2DownPressed())
			players[1]->y += -1;
		if (inputManager->isP2UpPressed())
			players[1]->y += 1;
		if (inputManager->isP2RightPressed())
			players[1]->x += 1;
		if (inputManager->isP2LeftPressed())
			players[1]->x += -1;

		if (inputManager->isP1Action1Pressed())
			printf("Player 1 Action Button 1 is pressed.\n");
		if (inputManager->isP1Action1Triggered())
			printf("Player 1 Action Button 1 is triggered.\n");
		if (inputManager->isP1Action1Released())
			printf("Player 1 Action Button 1 is released.\n");
		if (inputManager->isP1Action2Pressed())
			printf("Player 1 Action Button 2 is pressed.\n");
		if (inputManager->isP1Action2Released())
			printf("Player 1 Action Button 2 is released.\n");
		if (inputManager->isP1Action2Triggered())
			printf("Player 1 Action Button 2 is triggered.\n");

		if (inputManager->isP2Action1Pressed())
			printf("Player 2 Action Button 1 is pressed.\n");
		if (inputManager->isP2Action1Triggered())
			printf("Player 2 Action Button 1 is triggered.\n");
		if (inputManager->isP2Action1Released())
			printf("Player 2 Action Button 1 is released.\n");
		if (inputManager->isP2Action2Pressed())
			printf("Player 2 Action Button 2 is pressed.\n");
		if (inputManager->isP2Action2Released())
			printf("Player 2 Action Button 2 is released.\n");
		if (inputManager->isP2Action2Triggered())
			printf("Player 2 Action Button 2 is triggered.\n");



#pragma endregion Input

		//update screen buffer
		resources->Draw(pWindowSurface, players);

		//update screen
		SDL_UpdateWindowSurface(pWindow);

		//wait frames out
		frameRateController->WaitFrames();
		
	}
#pragma endregion Game Loop



	// Close if opened
	delete inputManager;
	delete resources;
	delete frameRateController;

	// Close and destroy the window
	SDL_DestroyWindow(pWindow);

	// Quit SDL subsystems
	SDL_Quit();
	
	return 0;
}