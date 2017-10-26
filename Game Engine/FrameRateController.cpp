/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	FrameRateController.cpp
Purpose:	Contains the definition of the methods of the FrameRateController class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_frameratecontrollercpp
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#include "FrameRateController.h"



FrameRateController::FrameRateController(float FrameTime)
{
	FrameTimeMax = FrameTime;
	currTime = SDL_GetTicks();
	newTime = 0.0f;
	t = 0.0f;
}

FrameRateController::~FrameRateController()
{
}

float FrameRateController::getDeltaTime()
{
	//update time
	newTime = SDL_GetTicks();
	dt = (newTime - currTime) / 1000.0f;
	currTime = newTime;
	return dt;
}

float FrameRateController::getTime()
{
	return t;
}

void FrameRateController::WaitFrames()
{
	do
	{
		newTime = SDL_GetTicks();
	} while ((newTime - currTime) < FrameTimeMax);
	t += dt;
}
