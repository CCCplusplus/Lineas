#include "raylib.h"
#include "raymath.h"
#include <vector>
#include <algorithm>

class Line{
private:

public:

	int x1, x2, y1, y2, steps, dx, dy;

	std::vector<int> e1, e2, e3;

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

	void drawTriangle(int xa, int ya, int xb, int yb, int xc, int yc, Color color)
	{
		drawPixelDDA(xa, ya, xb, yb, color);
		drawPixelDDA(xb, yb, xc, yc, color);
		drawPixelDDA(xc, yc, xa, ya, color);
	}

	void drawTriangleBresenham(int xa, int ya, int xb, int yb, int xc, int yc, Color color)
	{
		drawPixelBresenham(xa, ya, xb, yb, color);
		drawPixelBresenham(xb, yb, xc, yc, color);
		drawPixelBresenham(xc, yc, xa, ya, color);
	}

	void drawRect(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd, Color color)
	{
		drawPixelDDA(xa, ya, xb, yb, color);
		drawPixelDDA(xb, yb, xc, yc, color);
		drawPixelDDA(xc, yc, xd, yd, color);
		drawPixelDDA(xd, yd, xa, ya, color);
	}

	void drawRectBresenham(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd, Color color)
	{
		drawPixelBresenham(xa, ya, xb, yb, color);
		drawPixelBresenham(xb, yb, xc, yc, color);
		drawPixelBresenham(xc, yc, xd, yd, color);
		drawPixelBresenham(xd, yd, xa, ya, color);
	}

	void FillTriangleMaxMin(int xa, int ya, int xb, int yb, int xc, int yc, Color color)
	{
		int xmin = xa < xb ? xa : xb;
		xmin = xmin < xc ? xmin : xc;

		int ymin = ya < yb ? ya : yb;
		ymin = ymin < yc ? ymin : yc;

		int xmax = xa > xb ? xa : xb;
		xmax = xmax > xc ? xmax : xc;

		int ymax = ya > yb ? ya : yb;
		ymax = ymax > yc ? ymax : yc;

		for (int y = ymin; y <= ymax; y++) {
			std::vector<int> nodeX;

			
			if (ya != yb) StoreIntersection(xa, ya, xb, yb, y, nodeX);
			if (yb != yc) StoreIntersection(xb, yb, xc, yc, y, nodeX);
			if (yc != ya) StoreIntersection(xc, yc, xa, ya, y, nodeX);

			// Dibuja líneas horizontales entre los puntos de intersección
			std::sort(nodeX.begin(), nodeX.end());
			for (size_t i = 0; i < nodeX.size(); i += 2) {
				if (i + 1 < nodeX.size()) {
					drawPixelBresenham(nodeX[i], y, nodeX[i + 1], y, color);
				}
			}
		}
	}

	void FillCircle(int xc, int yc, int radius, Color color) 
	{
		for (int y = yc - radius; y <= yc + radius; y++) {
			// Calcula los puntos de intersección x para esta línea y
			int x1 = xc - sqrt(radius * radius - (y - yc) * (y - yc));
			int x2 = xc + sqrt(radius * radius - (y - yc) * (y - yc));

			drawPixelBresenham(x1, y, x2, y, color);
		}
	}

	void FillSquareWithTriangles(int xa, int ya, int xb, int yb, int xc, int yc, int xd, int yd, Color color)
	{
		FillTriangleMaxMin(xa, ya, xb, yb, xc, yc, color);

		FillTriangleMaxMin(xa, ya, xd, yd, xc, yc, color);
	}

	void StoreIntersection(int x1, int y1, int x2, int y2, int y, std::vector<int>& nodeX) {
		if (y1 == y2) return; // No intersección con líneas horizontales

		if (x1 == x2) { // Línea vertical
			if ((y >= std::min(y1, y2)) && (y <= std::max(y1, y2))) {
				nodeX.push_back(x1);
			}
		}
		else {
			float slope = (float)(y2 - y1) / (x2 - x1);
			float xIntersect = x1 + (y - y1) / slope;
			if ((y >= std::min(y1, y2)) && (y <= std::max(y1, y2))) {
				nodeX.push_back(static_cast<int>(round(xIntersect)));
			}
		}
	}
};