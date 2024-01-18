#include <iostream>
#include "raylib.h"
#include "Line.hpp"



int main()
{
    Color color = RED;
    Color background = WHITE;
    const int width = 600;
    const int height = 400;
    InitWindow(width, height, "window");
    SetTargetFPS(60);
    Line linea;

    linea.x1 = 0;
    linea.x2 = 600;
    linea.y1 = 0;
    linea.y2 = 400;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        

        //linea.drawPixelDDA(linea.x1, linea.y1, linea.x2, linea.y2, RED);

        //linea.drawPixelBresenham(400, 300, 80, 50, RED);

        linea.drawCircleOutline(200, 200, 50, RED);

        linea.drawCircleShape(200, 200, 50, RED);

        linea.drawCircleOutline(324, 324, 50, PINK);

        linea.drawCircleShape(324, 324, 50, PINK);

        linea.FillCircle(324, 324, 50, PINK);

        linea.drawTriangle(100, 100, 200, 100, 150, 50, BLUE);

        linea.FillTriangleMaxMin(100, 100, 200, 100, 150, 50, BLUE);

        linea.drawTriangleBresenham(300, 200, 350, 200, 325, 150, GREEN);

        linea.drawRect(450, 100, 550, 100, 550, 200, 450, 200, BLACK);

        linea.FillSquareWithTriangles(450, 100, 550, 100, 550, 200, 450, 200, BLACK);
        
        linea.drawRect(30, 200, 130, 200, 130, 300, 30, 300, DARKPURPLE);
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}