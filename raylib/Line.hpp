#include "raylib.h"
#include "raymath.h"

class Line{
private:

public:

float x1, x2, y1, y2, steps, dx, dy, Pk;


void drawPixelSimp(float xa, float ya, float xb, float yb, Color color) {

	dx = xb - xa;

	dy = yb - ya;

	if (abs(dx) >= abs(dy))
	{
		steps = dx;

		float xinc = dx / steps;
		float yinc = dy / steps;

		for (int i = 0; i < steps; i++)
		{
			DrawPixel(xa, ya, color);
			xa += xinc;
			ya += yinc;
		}
	}
	else
	{
		steps = dy;

		float xinc = dx / steps;
		float yinc = dy / steps;

		for (int i = 0; i < steps; i++)
		{
			DrawPixel(dx, dy, color);
			dx += xinc;
			dy += yinc;
		}
	}
}

void drawPixelBresenham(float xa, float ya, float xb, float yb, Color color)
{
	dx = xb - xa;
	dy = yb - ya;
	
	float p1 = 2 * dy - dx;
	float pk = p1;

	while (xa <= xb) 
	{
		if (pk > 0) 
		{
			float pnext = pk + (2 * dy) - (2 * dx);
			pk = pnext;
			DrawPixel(xa, ya, color);
			xa++;
		}
		else
		{
			float pnext = pk + (2 * dy);
			pk = pnext;
			DrawPixel(xa, ya, color);
			xa++;
			ya++;
		}
	}
}
};