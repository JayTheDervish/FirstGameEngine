/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Matrix2D.c
Purpose:	Contains the definition of the Matrix2D functions.
Language:	C
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_matrix2dc_1
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/6/2017

- End Header --------------------------------------------------------*/

#include "Matrix2D.h"

////////////////////
// From project 2 //
////////////////////

#define PI      3.1415926535897932384626433832795

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	pResult->m[0][0] = 1.0f;
	pResult->m[0][1] = 0.0f;
	pResult->m[0][2] = 0.0f;
	pResult->m[1][0] = 0.0f;
	pResult->m[1][1] = 1.0f;
	pResult->m[1][2] = 0.0f;
	pResult->m[2][0] = 0.0f;
	pResult->m[2][1] = 0.0f;
	pResult->m[2][2] = 1.0f;
}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{
	Matrix2D temp;
	temp.m[0][0] = pMtx->m[0][0];
	temp.m[0][1] = pMtx->m[1][0];
	temp.m[0][2] = pMtx->m[2][0];
	temp.m[1][0] = pMtx->m[0][1];
	temp.m[1][1] = pMtx->m[1][1];
	temp.m[1][2] = pMtx->m[2][1];
	temp.m[2][0] = pMtx->m[0][2];
	temp.m[2][1] = pMtx->m[1][2];
	temp.m[2][2] = pMtx->m[2][2];

	pResult->m[0][0] = temp.m[0][0];
	pResult->m[0][1] = temp.m[0][1];
	pResult->m[0][2] = temp.m[0][2];
	pResult->m[1][0] = temp.m[1][0];
	pResult->m[1][1] = temp.m[1][1];
	pResult->m[1][2] = temp.m[1][2];
	pResult->m[2][0] = temp.m[2][0];
	pResult->m[2][1] = temp.m[2][1];
	pResult->m[2][2] = temp.m[2][2];
}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{
	Matrix2D temp;

	temp.m[0][0] = (pMtx0->m[0][0] * pMtx1->m[0][0]) + (pMtx0->m[0][1] * pMtx1->m[1][0]) + (pMtx0->m[0][2] * pMtx1->m[2][0]);
	temp.m[0][1] = (pMtx0->m[0][0] * pMtx1->m[0][1]) + (pMtx0->m[0][1] * pMtx1->m[1][1]) + (pMtx0->m[0][2] * pMtx1->m[2][1]);
	temp.m[0][2] = (pMtx0->m[0][0] * pMtx1->m[0][2]) + (pMtx0->m[0][1] * pMtx1->m[1][2]) + (pMtx0->m[0][2] * pMtx1->m[2][2]);

	temp.m[1][0] = (pMtx0->m[1][0] * pMtx1->m[0][0]) + (pMtx0->m[1][1] * pMtx1->m[1][0]) + (pMtx0->m[1][2] * pMtx1->m[2][0]);
	temp.m[1][1] = (pMtx0->m[1][0] * pMtx1->m[0][1]) + (pMtx0->m[1][1] * pMtx1->m[1][1]) + (pMtx0->m[1][2] * pMtx1->m[2][1]);
	temp.m[1][2] = (pMtx0->m[1][0] * pMtx1->m[0][2]) + (pMtx0->m[1][1] * pMtx1->m[1][2]) + (pMtx0->m[1][2] * pMtx1->m[2][2]);

	temp.m[2][0] = (pMtx0->m[2][0] * pMtx1->m[0][0]) + (pMtx0->m[2][1] * pMtx1->m[1][0]) + (pMtx0->m[2][2] * pMtx1->m[2][0]);
	temp.m[2][1] = (pMtx0->m[2][0] * pMtx1->m[0][1]) + (pMtx0->m[2][1] * pMtx1->m[1][1]) + (pMtx0->m[2][2] * pMtx1->m[2][1]);
	temp.m[2][2] = (pMtx0->m[2][0] * pMtx1->m[0][2]) + (pMtx0->m[2][1] * pMtx1->m[1][2]) + (pMtx0->m[2][2] * pMtx1->m[2][2]);

	pResult->m[0][0] = temp.m[0][0];
	pResult->m[0][1] = temp.m[0][1];
	pResult->m[0][2] = temp.m[0][2];
	pResult->m[1][0] = temp.m[1][0];
	pResult->m[1][1] = temp.m[1][1];
	pResult->m[1][2] = temp.m[1][2];
	pResult->m[2][0] = temp.m[2][0];
	pResult->m[2][1] = temp.m[2][1];
	pResult->m[2][2] = temp.m[2][2];
}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x *p y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	pResult->m[0][0] = 1.0f;
	pResult->m[0][1] = 0.0f;
	pResult->m[0][2] = x;
	pResult->m[1][0] = 0.0f;
	pResult->m[1][1] = 1.0f;
	pResult->m[1][2] = y;
	pResult->m[2][0] = 0.0f;
	pResult->m[2][1] = 0.0f;
	pResult->m[2][2] = 1.0f;
}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x *p y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	pResult->m[0][0] = x;
	pResult->m[0][1] = 0.0f;
	pResult->m[0][2] = 0.0f;
	pResult->m[1][0] = 0.0f;
	pResult->m[1][1] = y;
	pResult->m[1][2] = 0.0f;
	pResult->m[2][0] = 0.0f;
	pResult->m[2][1] = 0.0f;
	pResult->m[2][2] = 1.0f;
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{
	Matrix2DRotRad(pResult, Angle * (PI / 180.0f));
}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{
	pResult->m[0][0] = cosf(Angle);
	pResult->m[0][1] = (-1.0f * sinf(Angle));
	pResult->m[0][2] = 0.0f;
	pResult->m[1][0] = sinf(Angle);
	pResult->m[1][1] = cosf(Angle);
	pResult->m[1][2] = 0.0f;
	pResult->m[2][0] = 0.0f;
	pResult->m[2][1] = 0.0f;
	pResult->m[2][2] = 1.0f;
}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{
	Vector2D temp;

	temp.x = (pMtx->m[0][0] * pVec->x) + (pMtx->m[0][1] * pVec->y) + (pMtx->m[0][2]);
	temp.y = (pMtx->m[1][0] * pVec->x) + (pMtx->m[1][1] * pVec->y) + (pMtx->m[1][2]);

	pResult->x = temp.x;
	pResult->y = temp.y;
}

// ---------------------------------------------------------------------------
