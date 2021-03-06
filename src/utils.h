#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>
#include <iostream>

namespace Utils
{
const int SLICES = 40;
const float PI = 3.141593f;
const float EPSILON = 0.1f;

struct Vec2
{
	float x, y;
	
	Vec2(void);
	Vec2(float argX, float argY);
	static float getSqrDistance(Vec2 argVec0, Vec2 argVec1);
	Vec2 getNormalized(void);
	Vec2 operator /(float argOperand);
	void operator +=(Vec2 argOther);
	void operator *=(float argOperand);
};
struct Color
{
	float red, green, blue, alpha;
	
	Color(void);
	Color(float argRed, float argGreen, float argBlue, float argAlpha = 1.0f);
	static Color getRandomColor(void);
};

void drawCircle(float argRadius, Color argColor, bool argFilled = true, bool argDashed = false);
void drawEnvelope(int argCount, bool argIsDest = false);
}

#endif //UTILS_H_INCLUDED
