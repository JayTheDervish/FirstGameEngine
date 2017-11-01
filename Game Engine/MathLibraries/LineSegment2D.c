/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	LineSegment2D.c
Purpose:	Contains the definition of the LineSegment2D functions.
Language:	C
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_linesegment2dc_1
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/6/2017

- End Header --------------------------------------------------------*/

#include "LineSegment2D.h"


int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
{
	LS->mP0.x = Point0->x;
	LS->mP0.y = Point0->y;

	LS->mP1.x = Point1->x;
	LS->mP1.y = Point1->y;

	Vector2D p0p1;

	Vector2DSub(&p0p1, Point1, Point0);

	LS->mN.x =  p0p1.y;
	LS->mN.y = -1.0f * p0p1.x;

	Vector2DNormalize(&LS->mN, &LS->mN);

	LS->mNdotP0 = Vector2DDotProduct(&LS->mN, &LS->mP0);

	return 0;
}