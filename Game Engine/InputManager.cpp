/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	InputManager.cpp
Purpose:	Contains the definition of the methods for the InputManager
			class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_inputmanagercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#include "InputManager.h"
#include <SDL.h>
#include<stdio.h>
#include <string.h>


//InputManager Constructor
//Parameters: numPlayers (1 or 2), mode k for keyboard or j for joystick
InputManager::InputManager(int numPlayers, char mode)
{
	if (numPlayers > 2 || numPlayers < 1)
		numberOfPlayers = 1;
	else
		numberOfPlayers = numPlayers;

	if (mode != 'k' && mode != 'j')
		inputMode = 'k';
	else
		inputMode = mode;

	SDL_InitSubSystem(SDL_INIT_JOYSTICK);

	//Joystick Mode
#pragma region Joystick Mode
	if (inputMode == 'j')
	{
		// Check for joystick
		if (SDL_NumJoysticks() > 0) {
			// Open joystick
			joy1 = SDL_JoystickOpen(0);

			if (joy1) {
				printf("Opened Joystick 0\n");
				printf("Name: %s\n", SDL_JoystickNameForIndex(0));
				printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy1));
				printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy1));
				printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy1));
			}
			else {
				printf("Couldn't open Joystick 0\n");
			}


			printf("\n");

			if (numberOfPlayers == 2)
			{
				joy2 = SDL_JoystickOpen(1);

				if (joy2) {
					printf("Opened Joystick 1\n");
					printf("Name: %s\n", SDL_JoystickNameForIndex(1));
					printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy2));
					printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy2));
					printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy2));
				}
				else {
					printf("Couldn't open Joystick 1\n");
				}
			}

			SDL_JoystickEventState(SDL_ENABLE);
		}
		else
			printf("No active joysticks attached\n");
	}
#pragma endregion

	else //mode == 'k' Keyboard Mode
	{
		//keyboard input startup
		//currentKeyboardState = SDL_GetKeyboardState(&length);

		memset(currentKeyboardState, SDL_GetKeyboardState(&length), length * sizeof(Uint8));

		prevKeyboardState = new Uint8();

		memset(prevKeyboardState, 0, length * sizeof(Uint8));
	}
}

InputManager::~InputManager()
{
	if (SDL_JoystickGetAttached(joy2)) {
		SDL_JoystickClose(joy2);
	}
	if (SDL_JoystickGetAttached(joy1)) {
		SDL_JoystickClose(joy1);
	}

}

int InputManager::GetP1Xpos()
{
	Sint16 x_move1 = 0;

	if (inputMode == 'j')
	{
		x_move1 = SDL_JoystickGetAxis(joy1, 0);

		if (x_move1 > 0) x_move1 = 1;
		else if (x_move1 < 0) x_move1 = -1;
	}
	else if (inputMode == 'k')
	{
		if (currentKeyboardState[SDL_SCANCODE_D])
			x_move1 = 1;
		else if (currentKeyboardState[SDL_SCANCODE_A])
			x_move1 = -1;
	}

	

	return x_move1;
}

int InputManager::GetP1Ypos()
{
	Sint16 y_move1 = 0;

	if (inputMode == 'j')
	{
		y_move1 = SDL_JoystickGetAxis(joy1, 1);

		if (y_move1 > 0) y_move1 = 1;
		else if (y_move1 < 0) y_move1 = -1;
	}
	else if (inputMode == 'k')
	{
		if (currentKeyboardState[SDL_SCANCODE_W])
			y_move1 = -1;
		else if (currentKeyboardState[SDL_SCANCODE_S])
			y_move1 = 1;
	}
	

	return y_move1;
}

int InputManager::GetP2Xpos()
{
	Sint16 x_move2 = 0;

	if (inputMode == 'j')
	{
		x_move2 = SDL_JoystickGetAxis(joy2, 0);

		if (x_move2 > 0) x_move2 = 1;
		else if (x_move2 < 0) x_move2 = -1;
	}
	else if (inputMode == 'k')
	{
		if (currentKeyboardState[SDL_SCANCODE_RIGHT])
			x_move2 = 1;
		else if (currentKeyboardState[SDL_SCANCODE_LEFT])
			x_move2 = -1;
	}

	return x_move2;
}

int InputManager::GetP2Ypos()
{
	Sint16 y_move2 = 0;

	if (inputMode == 'j')
	{
		y_move2 = SDL_JoystickGetAxis(joy2, 1);

		if (y_move2 > 0) y_move2 = 1;
		else if (y_move2 < 0) y_move2 = -1;
	}
	else if (inputMode == 'k')
	{
		if (currentKeyboardState[SDL_SCANCODE_UP])
			y_move2 = -1;
		else if (currentKeyboardState[SDL_SCANCODE_DOWN])
			y_move2 = 1;
	}

	return y_move2;
}


//Player 1
bool InputManager::isP1Action1Pressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[0] && prevJoystick1State[0])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_SPACE] && prevKeyboardState[SDL_SCANCODE_SPACE])
			return true;
	}
	return false;
}

bool InputManager::isP1Action1Triggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[0] && !prevJoystick1State[0])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_SPACE] && !prevKeyboardState[SDL_SCANCODE_SPACE])
			return true;
	}
	return false;
}

bool InputManager::isP1Action1Released()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick1State[0] && prevJoystick1State[0])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_SPACE] && prevKeyboardState[SDL_SCANCODE_SPACE])
			return true;
	}
	return false;
}

bool InputManager::isP1Action2Pressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[1] && prevJoystick1State[1])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_F] && prevKeyboardState[SDL_SCANCODE_F])
			return true;
	}
	return false;
}

bool InputManager::isP1Action2Triggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[1] && !prevJoystick1State[1])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_F] && !prevKeyboardState[SDL_SCANCODE_F])
			return true;
	}
	return false;
}

bool InputManager::isP1Action2Released()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick1State[1] && prevJoystick1State[1])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_F] && prevKeyboardState[SDL_SCANCODE_F])
			return true;
	}
	return false;
}

//Player 2
bool InputManager::isP2Action1Pressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[0] && prevJoystick2State[0])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_KP_0] && prevKeyboardState[SDL_SCANCODE_KP_0])
			return true;
	}
	return false;
}

bool InputManager::isP2Action1Triggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[0] && !prevJoystick2State[0])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_KP_0] && !prevKeyboardState[SDL_SCANCODE_KP_0])
			return true;
	}
	return false;
}

bool InputManager::isP2Action1Released()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick2State[0] && prevJoystick2State[0])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_KP_0] && prevKeyboardState[SDL_SCANCODE_KP_0])
			return true;
	}
	return false;
}

bool InputManager::isP2Action2Pressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[1] && prevJoystick2State[1])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_RCTRL] && prevKeyboardState[SDL_SCANCODE_RCTRL])
			return true;
	}
	return false;
}

bool InputManager::isP2Action2Triggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[1] && !prevJoystick2State[1])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_RCTRL] && !prevKeyboardState[SDL_SCANCODE_RCTRL])
			return true;
	}
	return false;
}

bool InputManager::isP2Action2Released()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick2State[1] && prevJoystick2State[1])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_RCTRL] && prevKeyboardState[SDL_SCANCODE_RCTRL])
			return true;
	}
	return false;
}

void InputManager::Update()
{

	if (inputMode == 'j')
	{
		//Copy current to previous
		prevJoystick1State[0] = currentJoystick1State[0];
		prevJoystick1State[1] = currentJoystick1State[1];

		if (numberOfPlayers == 2)
		{
			prevJoystick2State[0] = currentJoystick2State[0];
			prevJoystick2State[1] = currentJoystick2State[1];
		}

		//Update current
		SDL_JoystickUpdate();

		currentJoystick1State[0] = SDL_JoystickGetButton(joy1, 0);
		currentJoystick1State[1] = SDL_JoystickGetButton(joy1, 1);

		if (numberOfPlayers == 2)
		{
			currentJoystick2State[0] = SDL_JoystickGetButton(joy2, 0);
			currentJoystick2State[1] = SDL_JoystickGetButton(joy2, 1);
		}
	}
	else
	{
		//Copy current to previous
		memcpy(prevKeyboardState, currentKeyboardState, length * sizeof(Uint8));

		//Update Current
		memcpy(currentKeyboardState, SDL_GetKeyboardState(&length), length * sizeof(Uint8));
//		SDL_PumpEvents();
	}
	
}

