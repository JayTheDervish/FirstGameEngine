/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	README.txt
Purpose:	Contains the information on how to run the first milestone
		process for the final project
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_readme_1
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

To begin, there are two inputs that are changeable before compilation. Those 
are the two inputs to the InputManager constructor. The first argument is the 
number of players and the second is the mode of input. The first can be any number
and will default to 1 player, but it takes a maximum of 2 players. The second input
is the mode of input. A lower case 'j' will take joystick input and a 'k' will be for
keyboard input. The keyboard is chosen as default input if neither 'j' or 'k' is selected.
On compile the joystick mode is enabled and numPlayers = 2.

Player 1 movement maps to WASD, action buttons are  SPACE and F
Player 2 movement maps to arrow keys, action buttons are right control and 0 on num pad.

(Note: Controller is a Logitech Dual Action, but it should map 
one to one with an Xbox controller.) 

Note: Joystick mode is the only mode functioning correctly due to the following:
A non specified exception was thrown when I tried last using keyboard
input on the line while(SDL_PollEvents(&e)). I removed SDL_PumpEvents so it is not 
called twice, but I still received an exception that was not specified i.e. like 
heap corruption. My goal is to have both input styles working (keyboard worked
before I abstracted out the Resource Manager and Frame Rate Controller into their
own classes and outside of main) when the project is finished.
