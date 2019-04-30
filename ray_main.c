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


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


const int screenWidth = 800;
const int screenHeight = 640;

int Board[6][6]; // Y X
void setupboard(Texture2D scarfy, Texture2D board_pic);//ไว้เริ่มเล่นset upเกม
void viewboradnow();//ปริ้นกระดาษให้ดู
void movetroop(int x1, int y1, int x2, int y2);//เดิน กะ กิน เสด1ตัว
void summon(int player);//สุ่มเรียกตัวละคร ยังไม่เสด
void setup_troop_pic();//ตั้งเเค่ตัวละคร
void viewboradnum();//ดูรหัสตัวละครบนกระดาน
void filp_troop(int i);//กลับด้านตัวละคร
void SetColor(int ForgC);//ตั้งค่าสีตัวอักษร
void CanMove_map(int x, int y);//ฟังก์ชั่นเช็คว่าตัวนั้นเดินไปได้ไหม (ข้อมูลการเดินทั้งหมดอยู่ตรงนั้น)
struct Yroop{
    int x;
    int y;
    bool isAlive;
    int left;//เหลือกี่่ตัว
    int filp;
} troop[41];//สร้างไว้คราวๆก่อน 1-20 p1 21-40 p2   1เเละ21 เป็นDuke 0เป็นช่องว่าง

void drawMenu(); // Draw menu
void drawGameboard(Texture2D scarfy, Texture2D board_pic); // Draw game board
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
Vector2 position = { 90.0f, 70.0f };
int page = 0; // 0 is menu, 1 is game board, 2 is how to
int troop_tie = 1;
int setup_board = 0, SET_duke = 0;
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

    Image image = LoadImage("resources/board.png");
    ImageResize(&image, screenWidth, screenHeight);
    Texture2D board_pic = LoadTextureFromImage(image);

    Image imag = LoadImage("resources/Troop.png");        // Texture loading
    ImageResize(&imag, 7520, 95*0.9);
    Texture2D scarfy = LoadTextureFromImage(imag);

    

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
            if (setup_board == 0) {setupboard( scarfy,  board_pic);}
            else {drawGameboard( scarfy,board_pic);}
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

void drawGameboard(Texture2D scarfy, Texture2D board_pic) {
    Vector2 mousePoint;
    Rectangle hitbox_onboard[37];
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {int n = (i*6)+j;
            hitbox_onboard[n].x = 85+ (j*scarfy.width/76+5*j) ;
            hitbox_onboard[n].y = 68.0f +(i*scarfy.height-i*2);
            hitbox_onboard[n].width = scarfy.width/76+6;
            hitbox_onboard[n].height = scarfy.height-2 ;
        }}
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/76, (float)scarfy.height };
    frameRec.x = (2*1 + 1)*(float)scarfy.width/76;
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTexture(board_pic, 0, 0, WHITE);
        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) troop_tie += 1;
        //DrawTextureRec(scarfy, frameRec, position, WHITE);
        
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {int n = (i*6)+j;
                Vector2 position = {85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2)};//จัดใหม่
                frameRec.x = (2*Board[i][j])*(float)scarfy.width/76;
                DrawTextureRec(scarfy, frameRec, position, WHITE);
                mousePoint = GetMousePosition();
                 if (CheckCollisionPointRec(mousePoint, hitbox_onboard[n]))
            {
                DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, RED);

                //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page = i+1;
            }
            //else DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);
            }
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
void leftout(int i){
    if (troop[i].left != 0)
    {
        troop[i].left -= 1;
    }
}
void setupboard(Texture2D scarfy, Texture2D board_pic){
    srand(time(NULL));
    int i, j, ans = 0,jjj = 3,p = 21;
    for(i=0; i<=5; i++){
        for(j=0; j<=5; j++){
                Board[i][j] = 0;
        }
    }

    for(i = 1; i <= 41; i++)    {
        troop[i].left = 1;
        troop[i].filp = 0;
    }
    Board[0][1] = 0;//Bug
    
    while((SET_duke != 5)){
    Vector2 mousePoint;
    Rectangle hitbox_onboard[37];
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
            {int n = (i*6)+j;
            hitbox_onboard[n].x = 85+ (j*scarfy.width/76+5*j) ;
            hitbox_onboard[n].y = 68.0f +(i*scarfy.height-i*2);
            hitbox_onboard[n].width = scarfy.width/76+6;
            hitbox_onboard[n].height = scarfy.height-2 ;
            }}
    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/76, (float)scarfy.height };
    frameRec.x = (2*1)*(float)scarfy.width/76;
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(board_pic, 0, 0, WHITE);
    //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) troop_tie += 1;
    if (SET_duke == 0) DrawText("Playre 1\nPlan The Duke", screenWidth / 3, screenHeight /2, 50, RAYWHITE);//จัดใหม่
    if (SET_duke == 1||SET_duke == 4 ) DrawText("Playre 2\nPlan Footman", screenWidth / 2.5, screenHeight /4, 50, BLACK);
    if (SET_duke == 2||SET_duke == 3) DrawText("Playre 1\nPlan Footman", screenWidth / 2, screenHeight /4, 50, RAYWHITE);
    
    for (int i = 0; i < 6; i++)
    {
    for (int j = 0; j < 6; j++)
    {int n = (i*6)+j;
    troop[Board[i][j]].x =j;troop[Board[i][j]].y =i;
    mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, hitbox_onboard[n])){//ถ้าเมาส์อยู่ในช่อง
        Vector2 position = {85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2)};
        if (SET_duke == 0){//วาง Duke
        if (n == 33 || n == 32) {
        DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);  
        
        DrawTextureRec(scarfy, frameRec, position, WHITE);//หมากขาว

        frameRec.x = (2*21)*(float)scarfy.width/76;
        if (n == 33){jjj = 2;}
        else {jjj = 3;}
        Vector2 positionn = {85+ (jjj*scarfy.width/76+5*jjj),68.0f +(0*scarfy.height-0*2)};
        DrawTextureRec(scarfy, frameRec, positionn, WHITE);//หมากดำ
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//ถ้าเมาส์คลิกซ้าย
            {SET_duke = 1;
            ans = n;
            Board[5][ans-30] = 1;leftout(1);
            if (ans == 33){Board[0][2] = 21;}
            else{Board[0][3] = 21;}leftout(21);
            }
            }
            }
        if (SET_duke == 1||SET_duke == 4)
        {
        frameRec.x = (2*22 )*(float)scarfy.width/76;
        if((abs(troop[21].x-j)+abs(troop[21].y-i))==1&&(Board[i][j] == 0)){
            DrawTextureRec(scarfy, frameRec, position, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//ถ้าเมาส์คลิกซ้าย
            {p =1;
            if (SET_duke == 1) {Board[i][j] = 22;leftout(22);SET_duke = 2;}
            else if (SET_duke == 4) {Board[i][j] = 23;leftout(23);SET_duke = 5;}
            }
        }
        }
        if (SET_duke == 2||SET_duke == 3)
        {
        frameRec.x = (2*2 )*(float)scarfy.width/76;
        if((abs(troop[1].x-j)+abs(troop[1].y-i))==1&&(Board[i][j] == 0)){
            DrawTextureRec(scarfy, frameRec, position, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//ถ้าเมาส์คลิกซ้าย
            {
            if (SET_duke == 2) {Board[i][j] = 2;leftout(2);SET_duke = 3;p =1;}
            else if (SET_duke == 3){ Board[i][j] = 3;leftout(3);SET_duke = 4;p =21;}
            }
        }
        }
        

        
        }
    if (SET_duke == 1||SET_duke == 4)
        {
        Vector2 posi = {85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2)};//จัดใหม่
        frameRec.x = (2*Board[i][j] )*(float)scarfy.width/76;
        DrawTextureRec(scarfy, frameRec, posi, WHITE);
        if(((abs(troop[21].x-j)+abs(troop[21].y-i))==1)&&(Board[i][j] == 0)){
            DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), 10, 10, WHITE);
        }
        }
    else if (SET_duke == 2||SET_duke == 3)
        {
        Vector2 posi = {85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2)};//จัดใหม่
        frameRec.x = (2*Board[i][j])*(float)scarfy.width/76;
        DrawTextureRec(scarfy, frameRec, posi, WHITE);
        if(((abs(troop[1].x-j)+abs(troop[1].y-i))==1)&&(Board[i][j] == 0)){
            DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), 10, 10, WHITE);
        }
        }

        
    
    //else DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);
    }
    }

    EndDrawing();
    }
   
    setup_board+=1;
}
