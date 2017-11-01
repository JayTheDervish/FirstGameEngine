/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Vector2D.c
Purpose:	Contains the definition of the Vector2D functions.
Language:	C
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_vector2dc_1
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/6/2017

- End Header --------------------------------------------------------*/

#include "Vector2D.h"

#define EPSILON 0.0001
#define PI      3.1415926535897932384626433832795

////////////////////
// From Project 2 //
////////////////////

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = pResult->y = 0.0f;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	Vector2D temp;
	temp.x = (pVec0->x)* -1.0f;
	temp.y = (pVec0->y)* -1.0f;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	Vector2D temp;
	temp.x = pVec0->x + pVec1->x;
	temp.y = pVec0->y + pVec1->y;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	Vector2D temp;
	temp.x = pVec0->x - pVec1->x;
	temp.y = pVec0->y - pVec1->y;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	Vector2DScale(pResult, pVec0, 1.0f / (Vector2DLength(pVec0)));
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	Vector2D temp;
	temp.x = pVec0->x * c;
	temp.y = pVec0->y * c;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	Vector2D temp;
	temp.x = pVec1->x + (pVec0->x * c);
	temp.y = pVec1->y + (pVec0->y * c);
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	Vector2D temp;
	temp.x = (pVec0->x * c) - pVec1->x;
	temp.y = (pVec0->y * c) - pVec1->y;
	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	return sqrtf(Vector2DSquareLength(pVec0));
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	return Vector2DDotProduct(pVec0, pVec0);
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return sqrtf(Vector2DSquareDistance(pVec0, pVec1));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return ((pVec0->x - pVec1->x)*(pVec0->x - pVec1->x)) + ((pVec0->y - pVec1->y)*(pVec0->y - pVec1->y));
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	return (pVec0->x * pVec1->x) + (pVec0->y * pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	float radians = angle * (PI / 180.0f);
	Vector2DFromAngleRad(pResult, radians);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->x = cosf(angle);
	pResult->y = sinf(angle);
}

// ---------------------------------------------------------------------------

float Vector2DAngleFromVec2(Vector2D * pVec0)
{
	return atan2f(pVec0->y, pVec0->x);
}