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
		currentKeyboardState = SDL_GetKeyboardState(&length);

		//memset(currentKeyboardState, SDL_GetKeyboardState(&length), length * sizeof(Uint8));

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




//Player 1
#pragma region Player 1
bool InputManager::isP1RightPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[2] && prevJoystick1State[2])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_D] && prevKeyboardState[SDL_SCANCODE_D])
			return true;
	}
	return false;
}

bool InputManager::isP1RightTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[2] && !prevJoystick1State[2])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_D] && !prevKeyboardState[SDL_SCANCODE_D])
			return true;
	}
	return false;
}

bool InputManager::isP1RightReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick1State[2] && prevJoystick1State[2])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_D] && prevKeyboardState[SDL_SCANCODE_D])
			return true;
	}
	return false;
}

bool InputManager::isP1LeftPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[3] && prevJoystick1State[3])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_A] && prevKeyboardState[SDL_SCANCODE_A])
			return true;
	}
	return false;
}

bool InputManager::isP1LeftTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[3] && !prevJoystick1State[3])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_A] && !prevKeyboardState[SDL_SCANCODE_A])
			return true;
	}
	return false;
}

bool InputManager::isP1LeftReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick1State[3] && prevJoystick1State[3])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_A] && prevKeyboardState[SDL_SCANCODE_A])
			return true;
	}
	return false;
}

bool InputManager::isP1UpPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[4] && prevJoystick1State[4])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_W] && prevKeyboardState[SDL_SCANCODE_W])
			return true;
	}
	return false;
}

bool InputManager::isP1UpTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[4] && !prevJoystick1State[4])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_W] && !prevKeyboardState[SDL_SCANCODE_W])
			return true;
	}
	return false;
}

bool InputManager::isP1UpReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick1State[4] && prevJoystick1State[4])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_W] && prevKeyboardState[SDL_SCANCODE_W])
			return true;
	}
	return false;
}

bool InputManager::isP1DownPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[5] && prevJoystick1State[5])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_S] && prevKeyboardState[SDL_SCANCODE_S])
			return true;
	}
	return false;
}

bool InputManager::isP1DownTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick1State[5] && !prevJoystick1State[5])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_S] && !prevKeyboardState[SDL_SCANCODE_S])
			return true;
	}
	return false;
}

bool InputManager::isP1DownReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick1State[5] && prevJoystick1State[5])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_S] && prevKeyboardState[SDL_SCANCODE_S])
			return true;
	}
	return false;
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
#pragma endregion Player 1

//Player 2
#pragma region Player 2
bool InputManager::isP2UpPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[4] && prevJoystick2State[4])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_UP] && prevKeyboardState[SDL_SCANCODE_UP])
			return true;
	}
	return false;
}

bool InputManager::isP2UpTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[4] && !prevJoystick2State[4])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_UP] && !prevKeyboardState[SDL_SCANCODE_UP])
			return true;
	}
	return false;
}

bool InputManager::isP2UpReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick2State[4] && prevJoystick2State[4])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_UP] && prevKeyboardState[SDL_SCANCODE_UP])
			return true;
	}
	return false;
}

bool InputManager::isP2DownPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[5] && prevJoystick2State[5])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_DOWN] && prevKeyboardState[SDL_SCANCODE_DOWN])
			return true;
	}
	return false;
}

bool InputManager::isP2DownTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[5] && !prevJoystick2State[5])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_DOWN] && !prevKeyboardState[SDL_SCANCODE_DOWN])
			return true;
	}
	return false;
}

bool InputManager::isP2DownReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick2State[5] && prevJoystick2State[5])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_DOWN] && prevKeyboardState[SDL_SCANCODE_DOWN])
			return true;
	}
	return false;
}

bool InputManager::isP2RightPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[2] && prevJoystick2State[2])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_RIGHT] && prevKeyboardState[SDL_SCANCODE_RIGHT])
			return true;
	}
	return false;
}

bool InputManager::isP2RightTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[2] && !prevJoystick2State[2])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_RIGHT] && !prevKeyboardState[SDL_SCANCODE_RIGHT])
			return true;
	}
	return false;
}

bool InputManager::isP2RightReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick2State[2] && prevJoystick2State[2])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_RIGHT] && prevKeyboardState[SDL_SCANCODE_RIGHT])
			return true;
	}
	return false;
}

bool InputManager::isP2LeftPressed()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[3] && prevJoystick2State[3])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_LEFT] && prevKeyboardState[SDL_SCANCODE_LEFT])
			return true;
	}
	return false;
}

bool InputManager::isP2LeftTriggered()
{
	if (inputMode == 'j')
	{
		if (currentJoystick2State[3] && !prevJoystick2State[3])
			return true;
	}
	else
	{
		if (currentKeyboardState[SDL_SCANCODE_LEFT] && !prevKeyboardState[SDL_SCANCODE_LEFT])
			return true;
	}
	return false;
}

bool InputManager::isP2LeftReleased()
{
	if (inputMode == 'j')
	{
		if (!currentJoystick2State[3] && prevJoystick2State[3])
			return true;
	}
	else
	{
		if (!currentKeyboardState[SDL_SCANCODE_LEFT] && prevKeyboardState[SDL_SCANCODE_LEFT])
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
#pragma endregion Player 2



#pragma region Private Joystick Mapping
int InputManager::GetP1Ypos()
{
	Sint16 y_move1 = 0;

	
		y_move1 = SDL_JoystickGetAxis(joy1, 1);

		if (y_move1 > 0) y_move1 = 1;
		else if (y_move1 < 0) y_move1 = -1;

	

	return y_move1;
}

int InputManager::GetP2Xpos()
{
	Sint16 x_move2 = 0;

		x_move2 = SDL_JoystickGetAxis(joy2, 0);

		if (x_move2 > 0) x_move2 = 1;
		else if (x_move2 < 0) x_move2 = -1;
	

	return x_move2;
}

int InputManager::GetP2Ypos()
{
	Sint16 y_move2 = 0;

	
		y_move2 = SDL_JoystickGetAxis(joy2, 1);

		if (y_move2 > 0) y_move2 = 1;
		else if (y_move2 < 0) y_move2 = -1;
	
	return y_move2;
}

int InputManager::GetP1Xpos()
{
	Sint16 x_move1 = 0;

		x_move1 = SDL_JoystickGetAxis(joy1, 0);

		if (x_move1 > 0) x_move1 = 1;
		else if (x_move1 < 0) x_move1 = -1;
	


	return x_move1;
}

#pragma endregion Had to do this to map joysticks correctly



void InputManager::Update()
{

	if (inputMode == 'j')
	{
		//Copy current to previous
		prevJoystick1State[0] = currentJoystick1State[0];
		prevJoystick1State[1] = currentJoystick1State[1];
		prevJoystick1State[2] = currentJoystick1State[2];
		prevJoystick1State[3] = currentJoystick1State[3];
		prevJoystick1State[4] = currentJoystick1State[4];
		prevJoystick1State[5] = currentJoystick1State[5];

		if (numberOfPlayers == 2)
		{
			prevJoystick2State[0] = currentJoystick2State[0];
			prevJoystick2State[1] = currentJoystick2State[1];
			prevJoystick2State[2] = currentJoystick2State[2];
			prevJoystick2State[3] = currentJoystick2State[3];
			prevJoystick2State[4] = currentJoystick2State[4];
			prevJoystick2State[5] = currentJoystick2State[5];
		}

		//Update current
		SDL_JoystickUpdate();

		currentJoystick1State[0] = SDL_JoystickGetButton(joy1, 0);
		currentJoystick1State[1] = SDL_JoystickGetButton(joy1, 1);

		switch (GetP1Xpos())
		{
		case 1:
			currentJoystick1State[2] = 1;//right
			break;
		case -1:
			currentJoystick1State[3] = 1;//left
			break;
		case 0:
			currentJoystick1State[2] = 0;
			currentJoystick1State[3] = 0;
			break;
		default:
			break;
		}
		
		switch (GetP1Ypos())
		{
		case 1:
			currentJoystick1State[4] = 1; //up
			break;
		case -1:
			currentJoystick1State[5] = 1;//down
			break;
		case 0:
			currentJoystick1State[4] = 0;
			currentJoystick1State[5] = 0;
			break;
		default:
			break;
		}
		
		

		if (numberOfPlayers == 2)
		{
			currentJoystick2State[0] = SDL_JoystickGetButton(joy2, 0);
			currentJoystick2State[1] = SDL_JoystickGetButton(joy2, 1);

			switch (GetP2Xpos())
			{
			case 1:
				currentJoystick2State[2] = 1;//right
				break;
			case -1:
				currentJoystick2State[3] = 1;//left
				break;
			case 0:
				currentJoystick2State[2] = 0;
				currentJoystick2State[3] = 0;
				break;
			default:
				break;
			}

			switch (GetP2Ypos())
			{
			case 1:
				currentJoystick2State[4] = 1; //up
				break;
			case -1:
				currentJoystick2State[5] = 1;//down
				break;
			case 0:
				currentJoystick2State[4] = 0;
				currentJoystick2State[5] = 0;
				break;
			default:
				break;
			}
		}
	}
	else
	{
		//Copy current to previous
		memcpy(prevKeyboardState, currentKeyboardState, length * sizeof(Uint8));

		//Update Current
	//	memcpy(currentKeyboardState, SDL_GetKeyboardState(&length), length * sizeof(Uint8));
		SDL_PumpEvents();
	}
	
}

