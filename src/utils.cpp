#include "utils.h"

namespace Utils
{
//Vec2 struct...
Vec2::Vec2() {}
Vec2::Vec2(float argX, float argY)
: x(argX), y(argY) {};
float Vec2::getSqrDistance(Vec2 argVec0, Vec2 argVec1)
{
	return (pow(argVec0.x - argVec1.x, 2) + pow(argVec0.y - argVec1.y, 2));
}
Vec2 Vec2::getNormalized()
{
	float tempMag = sqrt(x * x + y * y);
	return Vec2(x / tempMag, y / tempMag);
}
Vec2 Vec2::operator /(float argOperand)
{
	return Vec2(x / argOperand, y / argOperand);
}
void Vec2::operator +=(Vec2 argOther)
{
	x += argOther.x;
	y += argOther.y;
}
void Vec2::operator *=(float argOperand)
{
	x *= argOperand;
	y *= argOperand;
}

//Color struct...
Color::Color(float argRed, float argGreen, float argBlue, float argAlpha /*= 1.0f*/)
: red(argRed), green(argGreen), blue(argBlue), alpha(argAlpha) {}
void drawCircle(float argRadius, Color argColor, bool argFilled/* = true*/, bool argDashed/*= false*/)
{
	glPushMatrix();
	if (argFilled)
	{
		glBegin(GL_TRIANGLE_FAN);
		glColor4f(argColor.red, argColor.green, argColor.blue, argColor.alpha);
		glVertex2f(0.0f, 0.0f);
		for (int i = 0; i < SLICES + 1; i++)
		{
			glVertex2f(argRadius * cos(i * 2.0f * PI / (float)SLICES), argRadius * sin(i * 2.0f * PI / (float)SLICES));
		}
		glEnd();
	}
	if (argDashed)
	{
		glPushAttrib(GL_LINE_BIT);
		glLineWidth(1.0f);
		glBegin(GL_LINES);
	}
	else
	{
		glPushAttrib(GL_LINE_BIT);
		glLineWidth(3.0f);
		glBegin(GL_LINE_STRIP);
	}
	glColor4f(argColor.red * 0.5f, argColor.green * 0.5f, argColor.blue * 0.5f, argColor.alpha);
	for (int i = 0; i < SLICES + 1; i++)
	{
		glVertex2f(argRadius * cos(i * 2.0f * PI / (float)SLICES), argRadius * sin(i * 2.0f * PI / (float)SLICES));
	}
	glEnd();
	glPopAttrib();
	glPopMatrix();
}
}
