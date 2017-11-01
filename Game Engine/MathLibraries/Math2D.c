/* Start Header -------------------------------------------------------

Copyright (C) 2017 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name:	Math2D.c
Purpose:	Contains the definition of the Math2D functions.
Language:	C
Platform:	Windows, MS C++ compiler, VS v140
Project:	jcoleman_CS529_math2dc_1
Author:		Jay Coleman j.coleman 60000217
Creation date: 10/6/2017

- End Header --------------------------------------------------------*/


#include "Math2D.h"
#include "stdio.h"

////////////////////
// From Project 1 //
////////////////////

#define PI      3.1415926535897932384626433832795

/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if (Vector2DSquareDistance(pP, pCenter) > (Radius * Radius))
		return 0;
	else
		return 1;
}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	float left, right, top, bottom;

	left = pRect->x - (Width / 2.0f);
	right = left + Width;
	top = pRect->y + (Height / 2.0f);
	bottom = top - Height;

	if (pPos->x < left || pPos->x > right || pPos->y < bottom || pPos->y > top)
		return 0;
	else
		return 1;
}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	if (Vector2DSquareDistance(pCenter0, pCenter1) > ((Radius0 + Radius1) * (Radius0 + Radius1)))
		return 0;
	else
		return 1;
}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	float left0, right0, top0, bottom0, left1, right1, top1, bottom1;

	left0 = pRect0->x - (Width0 / 2.0f);
	right0 = left0 + Width0;
	top0 = pRect0->y + (Height0 / 2.0f);
	bottom0 = top0 - Height0;

	left1 = pRect1->x - (Width1 / 2.0f);
	right1 = left1 + Width1;
	top1 = pRect1->y + (Height1 / 2.0f);
	bottom1 = top1 - Height1;

	if (left1 > right0 || left0 > right1 || top0 < bottom1 || top1 < bottom0)
		return 0;
	else
		return 1;
}


//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	return Vector2DDotProduct(&LS->mN, &P) - LS->mNdotP0;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{
	Vector2D PsPe, BiP0, P1P0, BiP1, P0P1;
	float t;

	Vector2DSub(&PsPe, Pe, Ps);
	t = (LS->mNdotP0 - (Vector2DDotProduct(&LS->mN, Ps))) / Vector2DDotProduct(&LS->mN, &PsPe);
	if (t > 0.0f && t < 1.0f)
	{
		Vector2DScaleAdd(Pi, &PsPe, Ps, t);
		Vector2DSub(&BiP0, Pi, &LS->mP0);
		Vector2DSub(&P1P0, &LS->mP1, &LS->mP0);
		Vector2DSub(&BiP1, Pi, &LS->mP1);
		Vector2DSub(&P0P1, &LS->mP0, &LS->mP1);
		if (Vector2DDotProduct(&BiP0, &P1P0) < 0 || Vector2DDotProduct(&BiP1, &P0P1) < 0)
			return -1.0f;
		return t;
	}
	return -1.0f;
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	float D = Radius;


	
	Vector2D PsPe, BiP0, P1P0, BiP1, P0P1;
	float t, t1, t2, nDotBs, nDotBe;

	nDotBs = Vector2DDotProduct(&LS->mN, Ps);
	nDotBe = Vector2DDotProduct(&LS->mN, Pe);


	if ((((nDotBs - LS->mNdotP0) < -D) &&  ((nDotBe - LS->mNdotP0) < -D))
		|| ( (nDotBs - LS->mNdotP0 > D) && ((nDotBe - LS->mNdotP0) > D)))
		return -1.0f;

	Vector2DSub(&PsPe, Pe, Ps);
	t1 = ((LS->mNdotP0 - (Vector2DDotProduct(&LS->mN, Ps))) + D)/ Vector2DDotProduct(&LS->mN, &PsPe);
	t2 = ((LS->mNdotP0 - (Vector2DDotProduct(&LS->mN, Ps))) - D) / Vector2DDotProduct(&LS->mN, &PsPe);
	if ((t1 > 0.0f && t1 < 1.0f) || (t2 > 0.0f && t2 < 1.0f))
	{
		if (t1 < t2) t = t1; else t = t2;

		if (t > 0.0f && t < 1.0f)
		{
			Vector2DScaleAdd(Pi, &PsPe, Ps, t);
			Vector2DSub(&BiP1, Pi, &LS->mP1);
			Vector2DSub(&P0P1, &LS->mP0, &LS->mP1);
			Vector2DSub(&BiP0, Pi, &LS->mP0);
			Vector2DSub(&P1P0, &LS->mP1, &LS->mP0);


			if ((Vector2DDotProduct(&BiP1, &P0P1) < 0)
				|| (Vector2DDotProduct(&BiP0, &P1P0) < 0))
				return -1.0f;
			return t;
		}
	}
	return -1.0f;
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	float t;
	Vector2D i;
	Vector2D iDotn2;
	
	t = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);
	Vector2DSub(&i, Pe, Pi);
	Vector2DScale(&iDotn2, &LS->mN, 2.0f * Vector2DDotProduct(&i, &LS->mN));
	Vector2DSub(R, &i, &iDotn2);

	return t;
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	float t;

	Vector2D i;
	Vector2D iDotn2;

	t = AnimatedCircleToStaticLineSegment(Ps, Pe, Radius, LS, Pi);
	if (t > 0.0f && t < 1.0f)
	{
		Vector2DSub(&i, Pe, Pi);
		Vector2DScale(&iDotn2, &LS->mN, 2.0f * Vector2DDotProduct(&i, &LS->mN));
		Vector2DSub(R, &i, &iDotn2);
		Vector2DAdd(Pe, R, Pi);
	}

	return t;
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{
	float a, b, c, delta, t, t0, t1, sqrtDelta, m;
	Vector2D v, CminusBs, vNormal, Neg2CminusBs;
	Vector2DSub(&v, Pe, Ps);
	Vector2DSub(&CminusBs, Center, Ps);
	Vector2DNormalize(&vNormal, &v);
	m = Vector2DDotProduct(&CminusBs, &vNormal);

	if ((m < 0 && ((Vector2DSquareLength(&CminusBs) > (Radius * Radius))) || ((Vector2DSquareLength(&CminusBs) -  (m * m))> (Radius * Radius))))
		return -1.0f;


	a = Vector2DDotProduct(&v, &v);
	Vector2DScale(&Neg2CminusBs, &CminusBs, -2.0f);
	b = Vector2DDotProduct(&Neg2CminusBs, &v);
	c = Vector2DDotProduct(&CminusBs, &CminusBs) - (Radius * Radius);

	delta = b * b - 4.0f * a * c;

	if (delta < 0.0f)
		return -1.0f;
	else if (delta == 0.0f) //grazes circle
	{
		t = (-1.0f * b) / (2.0f * a);
		if (t > 0.0f && t < 1.0f)
		{
			Vector2DScaleAdd(Pi, &v, Ps, t);
			return t;
		}
		else
			return -1.0f;
	}
	else if(delta > 0)//bigger than 0 so it hit
	{
		sqrtDelta = sqrtf(delta);
		t0 = (-1.0f * b - sqrtDelta) / (2.0f * a);
		t1 = (-1.0f * b + sqrtDelta) / (2.0f * a);
		t = fminf(t0, t1);
		if (t > 0 && t < 1)
		{
			Vector2DScaleAdd(Pi, &v, Ps, t);
			return t;
		}
		else
			return -1.0f;
	}
	return -1.0f;
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	float t;
	t = AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);
	
	if (t > 0.0f && t < 1.0f)
	{
		Vector2D n, normal, m, u, v, r;
		float k;
		Vector2DSub(&n, Pi, Center);
		Vector2DNormalize(&normal, &n);
		Vector2DSub(&m, Ps, Pi);
		Vector2DScale(&u, &normal, Vector2DDotProduct(&m, &normal));
		Vector2DScaleSub(R, &u, &m, 2.0f);
		Vector2DSub(&v, Pe, Ps);

		Vector2DNormalize(&r, R);
		k = Vector2DLength(&v);
		Vector2DScaleAdd(Pe, &r, Pi, k * (1.0f - t));
	}
	return t;
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{
	float t;
	t = AnimatedPointToStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi);
	return t;
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{
	float t;
	t = ReflectAnimatedPointOnStaticCircle(Center0s, Center0e, Center1, Radius0 + Radius1, Pi, R);
	
	return t;
}
