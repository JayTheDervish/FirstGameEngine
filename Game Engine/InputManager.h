/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	InputManager.h
Purpose:	Contains the declaration of the InputManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_inputmanagerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/


#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL_joystick.h>
#include <SDL_keyboard.h>

class InputManager
{
public:

	//Constructor
	InputManager(int numPlayers, char mode );

	//Deconstructor
	~InputManager();

	//Player 1 X movement
	int GetP1Xpos();

	//Player 1 Y movement
	int GetP1Ypos();

	//Player 2 X movement
	int GetP2Xpos();

	//Player 2 Y movement
	int GetP2Ypos();

	//Player 1 Action 1 Button
	//isPressed
	bool isP1Action1Pressed();

	//isTriggered
	bool isP1Action1Triggered();

	//isReleased
	bool isP1Action1Released();

	//Player 1 Action 2 Button
	//isPressed
	bool isP1Action2Pressed();

	//isTriggered
	bool isP1Action2Triggered();

	//isReleased
	bool isP1Action2Released();

	//Player 2 Action 1 Button
	//isPressed
	bool isP2Action1Pressed();

	//isTriggered
	bool isP2Action1Triggered();

	//isReleased
	bool isP2Action1Released();

	//Player 2 Action 2 Button
	//isPressed
	bool isP2Action2Pressed();

	//isTriggered
	bool isP2Action2Triggered();

	//isReleased
	bool isP2Action2Released();

	//Call to update Keyboard State
	void Update();

private:
	SDL_Joystick * joy1, *joy2;
	int numberOfPlayers;
	char inputMode;
	Uint8 * prevKeyboardState;
	const Uint8 * currentKeyboardState;
	int length;
	Uint8 currentJoystick1State[2];
	Uint8 currentJoystick2State[2];
	Uint8 prevJoystick1State[2];
	Uint8 prevJoystick2State[2];
};


#endif // !INPUTMANAGER_H


#pragma once
