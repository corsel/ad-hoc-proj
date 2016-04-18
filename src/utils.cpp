#include "utils.h"

namespace Utils
{
Color::Color(float argRed, float argGreen, float argBlue)
: red(argRed), green(argGreen), blue(argBlue) {}
void drawCircle(float argRadius, Color argColor, bool argFilled = true)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(argColor.red, argColor.green, argColor.blue);
	for (int i = 0; i < SLICES + 1; i++)
	{
		glVertex2f(argRadius * cos(2.0f * PI / SLICES), argRadius * sin(2.0f * PI / SLICES));
	}
	glEnd();
}
}
