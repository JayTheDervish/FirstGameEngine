/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	EventManager.h
Purpose:	Contains the declaration for the EventManager class.
Language:	C++
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_eventmanagerh
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/26/2017

- End Header --------------------------------------------------------*/

#pragma once

enum class EventType {COLLIDE, NUM};

#ifndef EventManager_h
#define EventManager_h

class EventManager
{
public:
	EventManager();
	~EventManager();

	void Event(EventType type);
	EventType mType;
private:

};
#endif // !EventManager_h

