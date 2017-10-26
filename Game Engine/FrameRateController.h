/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	FrameRateController.h
Purpose:	Contains the declaration of the FrameRateController class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_frameratecontrollerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/19/2017

- End Header --------------------------------------------------------*/

#ifndef FRAMERATECONTROLLER_H
#define FRAMERATECONTROLLER_H

#include <SDL_timer.h>

class FrameRateController
{
public:
	FrameRateController(float FrameTime);
	~FrameRateController();

	float getDeltaTime();
	float getTime();
	void WaitFrames();
private:
	float FrameTimeMax;
	float t, dt;
	float newTime, currTime;
};
#endif // !FRAMERATECONTROLLER_H



#pragma once
