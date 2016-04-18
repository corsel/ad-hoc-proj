#include <GL/gl.h>
#include <GL/freeglut.h>
#include <math.h>

namespace Utils
{
const int SLICES = 20;
const float PI = 3.141593f;
struct Vec2
{
	float x, y;
};
struct Color
{
	float red, green, blue;
	
	Color(float argRed, float argGreen, float argBlue);
};

void drawCircle(float argRadius, Color argColor, bool argFilled /* = true*/);
}
