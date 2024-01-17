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
        
        EndDrawing();
    }
    CloseWindow();
    return 0;
    
}