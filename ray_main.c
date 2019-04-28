/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "string.h"

const int screenWidth = 640;
const int screenHeight = 640;

void drawMenu(); // Draw menu
void drawGameboard(double starting); // Draw game board
struct GameBoard initializeBoard(); // Initialize board

typedef struct Troop {
    int type; //type 0-16
    int x;
    int y;
    bool isAlive;
    char owner[16];
};

typedef struct GameBoard {
    int size_x;
    int size_y;
    struct Troop mark[4][4];
};

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int page = 0; // 0 is menu, 1 is game board, 2 is how to
    double playingTime = 0;
    char testString[100];
    struct GameBoard board = initializeBoard(4, 4);

    InitWindow(screenWidth, screenHeight, "The Duke");
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        if (IsMouseButtonPressed(0)) page = !page; //0 is left click, 1 is right click
        
        // Draw
        //----------------------------------------------------------------------------------
        if (page == 0) {
            drawMenu();
        } else if (page == 1) {
            playingTime = GetTime();
            drawGameboard(playingTime);
        }
        
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

void drawMenu() {
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawText("The Duke", screenWidth / 2 - (10 * strlen("The Duke")), screenHeight / 2, 20, RAYWHITE);
    EndDrawing();
}

void drawGameboard(double starting) {
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        for (int i = 0; i < GetScreenWidth(); i++) {
            DrawPixel(i, (GetScreenHeight() / 2) + 100 * cos(starting + i * PI / 180), VIOLET);
        }
    EndDrawing();
}

struct GameBoard initializeBoard(int x, int y) {
    struct GameBoard board;
    board.size_x = x;
    board.size_y = y;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            //Troop troop;
            //board.mark[i][j] =
            break;
        }
    }    
    return board;
}