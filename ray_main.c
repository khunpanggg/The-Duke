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

const int screenWidth = 800;
const int screenHeight = 640;


void drawMenu(); // Draw menu
void drawGameboard(double starting); // Draw game board
struct GameBoard initializeBoard(); // Initialize board
Vector2 mousePoint;

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
int page = 0; // 0 is menu, 1 is game board, 2 is how to
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    
    double playingTime = 0;
    char testString[100];
    struct GameBoard board = initializeBoard(4, 4);

    InitWindow(screenWidth, screenHeight, "The Duke");

    bool selected[37] = { false };
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        //if (IsMouseButtonPressed(0)) page = !page; //0 is left click, 1 is right click
        
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
        DrawText("The Duke", screenWidth / 2 - (15 * strlen("The Duke")), screenHeight / 4, 50, RAYWHITE);
        mousePoint = GetMousePosition();
        Rectangle menuRecs[3];
        for (int i = 0; i < 3; i++)
        {
            menuRecs[i].x = screenWidth / 3;
            menuRecs[i].y = screenHeight *(2+(i*0.5))/ 4;
            menuRecs[i].width =300;
            menuRecs[i].height = 50;
        }

        for (int i = 0; i < 3; i++)    // Iterate along all the rectangles
        {
            if (CheckCollisionPointRec(mousePoint, menuRecs[i]))
            {
                DrawRectangle(screenWidth / 3, screenHeight *(2+(i*0.5))/ 4, 300, 50, RED);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page = i+1;
            }
            else DrawRectangle(screenWidth / 3, screenHeight *(2+(i*0.5))/ 4, 300, 50, GRAY);
        }
        
        DrawText("Start", screenWidth / 3+126, screenHeight *2/ 4+ 12, 25, RAYWHITE);
        DrawText("How to play", screenWidth / 3+60, screenHeight *2.5/ 4+ 12, 25, RAYWHITE);
        DrawText("Exit", screenWidth / 3+126, screenHeight *3/ 4+ 12, 25, RAYWHITE);

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