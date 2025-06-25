#include "include/raylib.h"

int main(void)
{
    int windowHeight = 1000;
    int windowWidth = 1000;
    const char* WINDOWNAME = "Flappy Dom";
    const int GAP = 50;

    InitWindow(windowWidth, windowHeight, WINDOWNAME);

    Rectangle dom = {
        .height = 30,
        .width = 30,
        .x = 300,
        .y = 470
    };

    Rectangle collum1 = {
        .height = GetRandomValue(10, windowHeight/2),
        .width = 50,
        .x = windowWidth,
        .y = 0, 
    };
    
    Rectangle collum2 = {
        .height = windowHeight - (collum1.height + GAP),
        .width = 50,
        .x = windowWidth,
        .y = windowHeight - (collum1.height + GAP), 
    };

    while (!WindowShouldClose())
    {
        collum1.x = collum2.x = collum1.x - GetFrameTime() * 100;

        BeginDrawing();

            ClearBackground(BLACK);

            DrawRectangleRec(dom, GREEN);
            DrawRectangleRec(collum1, RED);
            DrawRectangleRec(collum2, YELLOW);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
