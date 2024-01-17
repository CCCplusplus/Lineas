#include "raylib.h"
#include "raymath.h"

class Line{
private:

public:

	int x1, x2, y1, y2, steps, dx, dy;


	void drawPixelDDA(int xa, int ya, int xb, int yb, Color color) { //ahora con tiempo podemos reducir el codigo un poco

		dx = xb - xa;

		dy = yb - ya;

		steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

		float xinc = dx / (float)steps;
		float yinc = dy / (float)steps;

		float x = xa;
		float y = ya;

		for (int i = 0; i <= steps; i++) {
			DrawPixel(round(x), round(y), color);
			x += xinc;
			y += yinc;
		}
}

	void drawPixelBresenham(int xa, int ya, int xb, int yb, Color color)
	{
		//casos especiales
		if (xa == xb) {
			// Línea vertical
			int startY = ya < yb ? ya : yb;
			int endY = ya > yb ? ya : yb;
			for (int y = startY; y <= endY; y++) {
				DrawPixel(xa, y, color);
			}
			return;
		}
		if (ya == yb) {
			// Línea horizontal
			int startX = xa < xb ? xa : xb;
			int endX = xa > xb ? xa : xb;
			for (int x = startX; x <= endX; x++) {
				DrawPixel(x, ya, color);
			}
			return;
		}

		dx = fabs(xb - xa);
		dy = fabs(yb - ya);
	
		int sx = (xa < xb) ? 1 : -1;
		int sy = (ya < yb) ? 1 : -1;
		int err = (dx > dy ? dx : -dy) / 2, e2;

		while (true) {
			DrawPixel(xa, ya, color);
			if (xa == xb && ya == yb) break; // Cambie la condicion aqui por que no cerraba el circulo si la dejaba en el while
			e2 = err;
			if (e2 > -dx) {
				err -= dy;
				xa += sx;
			}
			if (e2 < dy) {
				err += dx;
				ya += sy;
			}
		}
	}

	void drawCircleOutline(int xc, int yc, int radius, Color color) {
		int angleStep = 10;
		for (int angle = 0; angle < 180; angle += angleStep) {
			float radStart = angle * (PI / 180.0f); 
			float radEnd = (angle + 180) * (PI / 180.0f); 
			// Puntos iniciales y finales de la línea
			int xs = xc + radius * cosf(radStart);
			int ys = yc + radius * sinf(radStart);
			int xe = xc + radius * cosf(radEnd);
			int ye = yc + radius * sinf(radEnd);
			drawPixelBresenham(xs, ys, xe, ye, color);
		}
	}

	void drawCircleShape(int xc, int yc, int radius, Color color) {
		int angleStep = 10; 
		for (int angle = 0; angle < 360; angle += angleStep) {
		
			float radStart = angle * (PI / 180.0f); 
			int xs = xc + radius * cosf(radStart);
			int ys = yc + radius * sinf(radStart);

			// Punto final en la circunferencia (siguiente punto a lo largo del círculo)
			float radEnd = (angle + angleStep) * (PI / 180.0f); 
			int xe = xc + radius * cosf(radEnd);
			int ye = yc + radius * sinf(radEnd);

			// Dibujar línea entre los puntos
			drawPixelBresenham(xs, ys, xe, ye, color);
		}
	}
};