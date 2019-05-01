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
void rotateBoard(); //หมุนกระดาน



struct Troop {

    int x;
    int y;
    bool isAlive;
    int left;//เหลือกี่่ตัว
    int filp;
} troop[41];//สร้างไว้คราวๆก่อน 1-20 p1 21-40 p2   1เเละ21 เป็นDuke 0เป็นช่องว่าง

void drawMenu(); // Draw menu
void drawGameboard(Texture2D scarfy, Texture2D board_pic); // Draw game board

Vector2 mousePoint;
Vector2 position = { 90.0f, 70.0f };
int page = 0; // 0 is menu, 1 is game board, 2 is how to
int page_howto = 0;
int troop_tie = 1;
int setup_board = 0, SET_duke = 0, player = 0, selecty = 99, selectx = 99;
Font fontTtf;
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------

    double playingTime = 0;
    char testString[100];
    page_howto = 0;

    InitWindow(screenWidth, screenHeight, "The Duke");
    Image background = LoadImage("resources/background.png");
    Image dukelogo = LoadImage("resources/dukelogo.png");
    Texture2D texture = LoadTextureFromImage(background);
    Texture2D logo = LoadTextureFromImage(dukelogo);
    
    Image howto_1 = LoadImage("resources/howtoplay/1.png");
    ImageResize(&howto_1, screenWidth, screenHeight);
    Texture2D howto1 = LoadTextureFromImage(howto_1);
    
    Image howto_2 = LoadImage("resources/howtoplay/2.png");
    ImageResize(&howto_2, screenWidth, screenHeight);
    Texture2D howto2 = LoadTextureFromImage(howto_2);
    
    Image howto_3 = LoadImage("resources/howtoplay/3.png");
    ImageResize(&howto_3, screenWidth, screenHeight);
    Texture2D howto3 = LoadTextureFromImage(howto_3);
    
    Image howto_4 = LoadImage("resources/howtoplay/4.png");
    ImageResize(&howto_4, screenWidth, screenHeight);
    Texture2D howto4 = LoadTextureFromImage(howto_4);

    Image howto_5 = LoadImage("resources/howtoplay/5.png");
    ImageResize(&howto_5, screenWidth, screenHeight);
    Texture2D howto5 = LoadTextureFromImage(howto_5);

    Image howto_6 = LoadImage("resources/howtoplay/6.png");
    ImageResize(&howto_6, screenWidth, screenHeight);
    Texture2D howto6 = LoadTextureFromImage(howto_6);

    Image howto_7 = LoadImage("resources/howtoplay/7.png");
    ImageResize(&howto_7, screenWidth, screenHeight);
    Texture2D howto7 = LoadTextureFromImage(howto_7);

    Image howto_8 = LoadImage("resources/howtoplay/8.png");
    ImageResize(&howto_8, screenWidth, screenHeight);
    Texture2D howto8 = LoadTextureFromImage(howto_8);

    Image howto_9 = LoadImage("resources/howtoplay/9.png");
    ImageResize(&howto_9, screenWidth, screenHeight);
    Texture2D howto9 = LoadTextureFromImage(howto_9);

    Image howto_10 = LoadImage("resources/howtoplay/10.png");
    ImageResize(&howto_10, screenWidth, screenHeight);
    Texture2D howto10 = LoadTextureFromImage(howto_10);

    Image howto_11 = LoadImage("resources/howtoplay/11.png");
    ImageResize(&howto_11, screenWidth, screenHeight);
    Texture2D howto11 = LoadTextureFromImage(howto_11);

    Image howto_12 = LoadImage("resources/howtoplay/12.png");
    ImageResize(&howto_12, screenWidth, screenHeight);
    Texture2D howto12 = LoadTextureFromImage(howto_12);

    Image howto_13 = LoadImage("resources/howtoplay/13.png");
    ImageResize(&howto_13, screenWidth, screenHeight);
    Texture2D howto13 = LoadTextureFromImage(howto_13);

    Image howto_14 = LoadImage("resources/howtoplay/14.png");
    ImageResize(&howto_14, screenWidth, screenHeight);
    Texture2D howto14 = LoadTextureFromImage(howto_14);

    Image howto_15 = LoadImage("resources/howtoplay/15.png");
    ImageResize(&howto_15, screenWidth, screenHeight);
    Texture2D howto15 = LoadTextureFromImage(howto_15);

    Image howto_16 = LoadImage("resources/howtoplay/16.png");
    ImageResize(&howto_16, screenWidth, screenHeight);
    Texture2D howto16 = LoadTextureFromImage(howto_16);

    Image howto_17 = LoadImage("resources/howtoplay/17.png");
    ImageResize(&howto_17, screenWidth, screenHeight);
    Texture2D howto17 = LoadTextureFromImage(howto_17);

    Image howto_18 = LoadImage("resources/howtoplay/18.png");
    ImageResize(&howto_18, screenWidth, screenHeight);
    Texture2D howto18 = LoadTextureFromImage(howto_18);

    Image howto_19 = LoadImage("resources/howtoplay/19.png");
    ImageResize(&howto_19, screenWidth, screenHeight);
    Texture2D howto19 = LoadTextureFromImage(howto_19);

    Image howto_20 = LoadImage("resources/howtoplay/20.png");
    ImageResize(&howto_20, screenWidth, screenHeight);
    Texture2D howto20 = LoadTextureFromImage(howto_20);

    Image howto_21 = LoadImage("resources/howtoplay/21.png");
    ImageResize(&howto_21, screenWidth, screenHeight);
    Texture2D howto21 = LoadTextureFromImage(howto_21);

    Image howto_22 = LoadImage("resources/howtoplay/22.png");
    ImageResize(&howto_22, screenWidth, screenHeight);
    Texture2D howto22 = LoadTextureFromImage(howto_22);

    fontTtf = LoadFont("resources/fonts/piecesofeight.ttf");

    bool selected[37] = { false };
    SetTargetFPS(60);

    Image image = LoadImage("resources/board.png");
    ImageResize(&image, screenWidth, screenHeight);
    Texture2D board_pic = LoadTextureFromImage(image);

    Image imag = LoadImage("resources/Troop.png");        // Texture loading
    ImageResize(&imag, 7520, 95*0.9);
    Texture2D scarfy = LoadTextureFromImage(imag);

    //ToggleFullscreen();

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
            drawMenu(texture, logo);
        } else if (page == 1) {
            if (setup_board == 0) {
                setupboard(scarfy, board_pic);
            }
            else {
                drawGameboard(scarfy, board_pic);
            }
        }
        else if (page == 2) {
            if (page_howto == 0) {
                drawHowTo(howto1);
            } else if (page_howto == 1) {
                drawHowTo(howto2);
            } else if (page_howto == 2) {
                drawHowTo(howto3);
            } else if (page_howto == 3) {
                drawHowTo(howto4);
            } else if (page_howto == 4) {
                drawHowTo(howto5);
            } else if (page_howto == 5) {
                drawHowTo(howto6);
            } else if (page_howto == 6) {
                drawHowTo(howto7);
            } else if (page_howto == 7){
                drawHowTo(howto8);
            } else if (page_howto == 8){
                drawHowTo(howto9);
            } else if (page_howto == 9){
                drawHowTo(howto10);
            } else if (page_howto == 10){
                drawHowTo(howto11);
            } else if (page_howto == 11){
                drawHowTo(howto12);
            } else if (page_howto == 12){
                drawHowTo(howto13);
            } else if (page_howto == 13){
                drawHowTo(howto14);
            } else if (page_howto == 15){
                drawHowTo(howto16);
            } else if (page_howto == 17){
                drawHowTo(howto18);
            } else if (page_howto == 19){
                drawHowTo(howto20);
            } else if (page_howto == 20){
                drawHowTo(howto21);
            } else if (page_howto == 21){
                drawHowTo(howto22);
            } else {
                page = 0;
                page_howto = 0;
            }
        }
        else if (page == 3){
            drawCredits();
        }
        else if (page == 4) { //Exit
            CloseWindow();
        }

        
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

void drawMenu(Texture2D texture, Texture2D logo) {
    BeginDrawing();
    
        ClearBackground(LIGHTGRAY);
        //DrawText("The Duke", screenWidth / 2 - (15 * strlen("The Duke")), screenHeight / 4, 50, RAYWHITE);
        DrawTexture(texture , 0, 0, WHITE);
        DrawTexture(logo , screenWidth/3 -140, screenHeight/4 - 80, WHITE);

        mousePoint = GetMousePosition();
        Rectangle menuRecs[4];
        for (int i = 0; i < 4; i++)
        {
            menuRecs[i].x = screenWidth / 3;
            menuRecs[i].y = screenHeight *(2+(i*0.4))/ 4;
            menuRecs[i].width = 300;
            menuRecs[i].height = 50;
        }

        for (int i = 0; i < 4; i++)    // Iterate along all the rectangles
        {
            if (CheckCollisionPointRec(mousePoint, menuRecs[i]))
            {
                DrawRectangle(screenWidth / 3, screenHeight *(2+(i*0.4))/ 4, 300, 50, RED);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page = i + 1;
            }
            else DrawRectangle(screenWidth / 3, screenHeight *(2+(i*0.4))/ 4, 300, 50, DARKBROWN);
        }
        Vector2 vec1 = {screenWidth / 3 + 110, screenHeight *2/ 4+ 2};
        Vector2 vec2 = {screenWidth / 3 + 50, screenHeight *2.4/ 4+ 2};
        Vector2 vec3 = {screenWidth / 3 + 100, screenHeight *2.8/ 4 + 2};
        Vector2 vec4 = {screenWidth / 3 + 120, screenHeight *3.2/ 4 + 2};
        //DrawTextEx(Font font, const char* text, Vector2 position, int fontsize, int padding, Color tint);
        DrawTextEx(fontTtf, "Start", vec1, 55, 0, GOLD);
        DrawTextEx(fontTtf, "How to play", vec2, 55, 0, GOLD);
        DrawTextEx(fontTtf, "Credits", vec3, 55, 0, GOLD);
        DrawTextEx(fontTtf, "Exit", vec4, 55, 0, GOLD);
    EndDrawing();
}

void drawGameboard(Texture2D scarfy, Texture2D board_pic) {
    Vector2 mousePoint;
    Rectangle hitbox_onboard[37];
    Rectangle summonbox= {screenWidth / 4+126, screenHeight *3/ 4+ 12, 25};
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            int n = (i*6)+j;
            hitbox_onboard[n].x = 85+ (j*scarfy.width/76+5*j) ;
            hitbox_onboard[n].y = 68.0f +(i*scarfy.height-i*2);
            hitbox_onboard[n].width = scarfy.width/76+6;
            hitbox_onboard[n].height = scarfy.height-2 ;
        }
    }

    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/76, (float)scarfy.height };
    //frameRec.x = (2*1 + 1)*(float)scarfy.width/76;
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTexture(board_pic, 0, 0, WHITE);
        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) troop_tie += 1;
        //DrawTextureRec(scarfy, frameRec, position, WHITE);
        
        for (int i = 0; i < 6; i++)
        {
            for (int j = 0; j < 6; j++)
            {
                int n = (i*6)+j;
                troop[Board[i][j]].x = j;
                troop[Board[i][j]].y = i;
                Vector2 position = {85+ (j*scarfy.width/76+5*j), 68.0f +(i*scarfy.height-i*2)};//จัดใหม่
                frameRec.x = (2*Board[i][j]+troop[Board[i][j]].filp)*(float)scarfy.width/76;
                DrawTextureRec(scarfy, frameRec, position, WHITE);
                mousePoint = GetMousePosition();
                if (selectx+selecty != 198)
                {
                    if (CanMove(Board[selecty][selectx],j,i))
                    {
                        DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76/8+6, scarfy.height/8-2, RED);
                        if (Can_summon(player,Board[selecty][selectx]))
                        { DrawText("Summon", screenWidth / 4+126, screenHeight *3/ 4+ 80, 25, RAYWHITE);
                        DrawRectangle(screenWidth / 4+26, screenHeight *3/ 4+ 100, 150, 50, BEIGE);
                        }
                    }
                }
                if (CheckCollisionPointRec(mousePoint, hitbox_onboard[n]))
                {
                    if (((Board[i][j]>=21) && player>0) || ((Board[i][j]<21) && player<1 && Board[i][j]!=0))
                    {
                        DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76/8+6, scarfy.height/8-2, BLUE);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//ถ้าเมาส์คลิกซ้าย
                        {
                            selectx = j;
                            selecty = i;
                        }
                    }
                    else if (selectx+selecty != 198&&CanMove(Board[selecty][selectx],j,i)&&IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                    {
                        movetroop(selectx,selecty,j,i);
                        if(player==1) {
                            player = 0;
                            selectx=99;
                            selecty=99; 
                        }
                        else {
                            player = 1;
                            selectx=99;
                            selecty=99; 
                        }

                        rotateBoard();
                    }   
                    //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page = i+1;(scarfy, frameRec, position, WHITE
                }
                //else DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);
            }
        }
        //DrawTextureEx(scarfy, Vector2 position, float rotation, float scale, Color tint);
        DrawText(FormatText("player%i selectx%i selecty%i",player ,selectx,selecty), 10, 40, 20, LIGHTGRAY);
    EndDrawing();
}
void drawCredits(Texture2D texture){
    BeginDrawing();
        DrawTexture(texture , 0, 0, WHITE);
        Vector2 vec0 = {360, 50};
        Vector2 vec1 = {180, 120};
        Vector2 vec2 = {180, 170};
        Vector2 vec3 = {180, 220};
        Vector2 vec4 = {180, 270};
        Vector2 vec5 = {330, 320};
        Vector2 vec6 = {150, 390};
        Vector2 vec7 = {150, 440};
        Vector2 vec8 = {150, 490};
        Vector2 vec9 = {150, 540};
        DrawTextEx(fontTtf, "Member", vec0, 55, 0, GOLD);
        DrawTextEx(fontTtf, "61070004  Krittima Chantachalee", vec1, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "61070016  Kittiwat Boonpean", vec2, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "61070059  Nichapat Kachacheewa", vec3, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "61070200  Woramat Ngamkham", vec4, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "Credit Game", vec5, 55, 0, GOLD);
        DrawTextEx(fontTtf, "Designers - Jeremy Holcomb Stephen McLaughlin", vec6, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "Artist - Matt Heerdt", vec7, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "Publisher - Catalyst Game Labs", vec8, 40, 0, LIGHTGRAY);
        DrawTextEx(fontTtf, "Mechanisms - Grid Movement Tile Placement", vec9, 40, 0, LIGHTGRAY);
        
        Rectangle menuBack[0];
        mousePoint = GetMousePosition();
        Vector2 vec = {670, 580};
        menuBack[0].x = 600;
        menuBack[0].y = 580;
        menuBack[0].width = 200;
        menuBack[0].height = 50;
        if (CheckCollisionPointRec(mousePoint, menuBack[0])){
                DrawRectangle(600, 580, 200, 45, RED);
                DrawTextEx(fontTtf, "Back", vec, 45, 0, GOLD);

                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                    page = 0;
                }
            }
            else DrawRectangle(600, 580, 200, 45, DARKBROWN);
                DrawTextEx(fontTtf, "Back", vec, 45, 0, GOLD);



    EndDrawing();
}
void drawHowTo(Texture2D howto1) {
    BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTexture(howto1, 0, 0, WHITE);
        //DrawRectangle(screenWidth/2 - 250, screenHeight/2 - 250, 500, 500, BLACK);
        //DrawRectangle(screenWidth/2 - 242.5, screenHeight/2 - 242.5, 485, 485, RAYWHITE);
        Rectangle menuNext[3];
        mousePoint = GetMousePosition();
        for (int i = 0; i < 2; i++)
        {
            menuNext[i].x = 170 +(i*200);
            menuNext[i].y = 570;
            menuNext[i].width = 150;
            menuNext[i].height = 40;
        }

        for (int i = 0; i < 2; i++)    // Iterate along all the rectangles
        {
            Vector2 vec = {menuNext[i].x+60, menuNext[i].y+5};

           if (CheckCollisionPointRec(mousePoint, menuNext[i])) {
                if(i==0 && page_howto != 0){
                    DrawRectangle(menuNext[i].x, menuNext[i].y, 190, 55, RED);
                    DrawTextEx(fontTtf, "Back", vec, 55, 0, GOLD);

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        page_howto = page_howto > 0 ? page_howto - 1 : 0;
                    }
                }
                if(i==1){
                    DrawRectangle(menuNext[i].x, menuNext[i].y, 190, 55, RED);
                    DrawTextEx(fontTtf, "Next", vec, 55, 0, GOLD);

                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                        page_howto = page_howto < 21 ? page_howto + 1 : 21;
                    }

                }
            }
            else if (i==0 && page_howto != 0){
                DrawRectangle(menuNext[i].x, menuNext[i].y, 190, 55, DARKBROWN);
                DrawTextEx(fontTtf, "Back", vec, 55, 0,GOLD);
            }
            else if (i==1){
                DrawRectangle(menuNext[i].x, menuNext[i].y, 190, 55, DARKBROWN);
                DrawTextEx(fontTtf, "Next", vec, 55, 0,GOLD);
            }
        }
    EndDrawing();
}

void leftout(int i){
    if (troop[i].left != 0)
    {
        troop[i].left -= 1;
    }
}

void movetroop(int x1, int y1, int x2, int y2){
    Board[y2][x2] = Board[y1][x1];
    Board[y1][x1] = 0;
    filp_troop(Board[y2][x2]);
}

void filp_troop(int k){
    if (troop[k].filp == 1)
    {
        troop[k].filp = 0;
    }
    else
    {
        troop[k].filp = 1;
    }
}
int Can_summon(int p,int troop){
    if ((troop ==21)&&((p ==1)))
    {
        return 1;
    }
    else if((troop ==1)&&((p ==0)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void summon(int p){
    int x=99,y=99, pl =20*(p)+1,re;
    if (p == 0 )
    {
        re = rand()%17;
    }
    else 
    {
        re = (rand()%17)+21;
    }

    if (troop[re].left == 0)
    {
        summon(pl);
    }
    else
    {
        while((abs(troop[pl].x-x)+abs(troop[pl].y-y))!=1 && Is_ally(troop[pl], Board[y][x])!= 1){
            //printf("X Y\n");
            //scanf("%d %d,",&x,&y);}
            }
            Board[y][x] = re;
            leftout(re);
            troop[re].x = x;
            troop[re].y = y;
        
    }
}

int Is_ally(int numA, int numB){
    if ((numA >=21)&&((numB >=21)))
    {
        return 1;
    }
    else if (((numA <21)&& (numA != 0))&&((numB <21)&& (numB != 0)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int Is_enemy(int numA, int numB){
    if ((numA >=21)&&((numB <21)&& (numB != 0)))
    {
        return 1;
    }
    else if((numB >=21)&&((numA <21)&& (numA != 0)))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CanMove_map(int x, int y){
    int i, j;
    for (i = 0; i <= 5; i++){
        for (j = 0; j <= 5; j++){
            if (CanMove(Board[y][x], j, i) != 0)
            {
                /**/
            }
            //else if((i==y)&&(j==x)){if (troop[Board[y][x]].filp == 0){printf("i ");}
            //else if (troop[Board[y][x]].filp == 1){printf("I ");} 
        }
            //else{printf("- ");}
        //if (j == 5) {printf(" %d \n", i);}
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
        {
            int n = (i*6)+j;
            hitbox_onboard[n].x = 85+ (j*scarfy.width/76+5*j) ;
            hitbox_onboard[n].y = 68.0f +(i*scarfy.height-i*2);
            hitbox_onboard[n].width = scarfy.width/76+6;
            hitbox_onboard[n].height = scarfy.height-2 ;
        }
    }

    Rectangle frameRec = { 0.0f, 0.0f, (float)scarfy.width/76, (float)scarfy.height };
    frameRec.x = (2*1)*(float)scarfy.width/76;
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(board_pic, 0, 0, WHITE);
    //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) troop_tie += 1;
    if (SET_duke == 0) DrawText("Player 1\nPlan The Duke", screenWidth / 3, screenHeight /2, 50, RAYWHITE);//จัดใหม่
    if (SET_duke == 1||SET_duke == 4 ) DrawText("Player 2\nPlan Footman", screenWidth / 2.5, screenHeight /4, 50, BLACK);
    if (SET_duke == 2||SET_duke == 3) DrawText("Player 1\nPlan Footman", screenWidth / 2, screenHeight /4, 50, RAYWHITE);
    
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
        DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/8/76+6, scarfy.height/8-2, BLUE);  
        
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
            DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), 10, 10, BLUE);
        }
        }
    else if (SET_duke == 2||SET_duke == 3)
    {
        Vector2 posi = {85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2)};//จัดใหม่
        frameRec.x = (2*Board[i][j])*(float)scarfy.width/76;
        DrawTextureRec(scarfy, frameRec, posi, WHITE);
        if(((abs(troop[1].x-j)+abs(troop[1].y-i))==1)&&(Board[i][j] == 0)){
            DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), 10, 10, BLUE);
        }
    }
    //else DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);
        }
    }

    EndDrawing();
    }
   
    setup_board+=1;
}

void rotateBoard() {
    int newBoard[6][6];
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 6; x++) {
            int t_id = Board[y][x];
            troop[t_id].x = 5 - x;
            troop[t_id].y = 5 - y;
            newBoard[5 - y][5 - x] = t_id;
        }
    }

    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 6; x++) {
            Board[y][x] = newBoard[y][x];
        }
    }
}


int CanMove(int num,int x,int y){ //1,21 = duke  
    int i,j,k, distance, ABSdis, disx, disy, tnx= troop[num].x,tny = troop[num].y; //2-4,22-24 = footman
    //if (num >= 21) y = abs(5-y);
    disx = x-troop[num].x;disy =y-troop[num].y;distance = abs(disy)+abs(disx);//5-7, 25-27 = PikeMan
    if (Is_ally(num, Board[y][x]))  {return 0;}//8, 28 = Assassin                  
    if (num == 1|| num == 21)//Duke             9, 29 = Bowman
    { if (troop[num].filp == 0)// %i%           10, 30 = champion
        {distance = x-troop[num].x ;            //11, 31 = Gragoon
            if (distance == 0 || y != troop[num].y){return 0;}//12,32 = General
            ABSdis = abs(distance);             //14, 34  == Knight
            for (i = 1; i <= ABSdis; i++){      //15, 35 == Marsall
                if (distance < 1)   {k = i*-1;}else{k = i;}
                if (Board[y][k+troop[num].x] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[y][k+troop[num].x])))
                    {
                        return 1;
                    }
                    else{ return 0;}
                }
            }
            return 1;
            
        }
        else if (troop[num].filp == 1){// %
            distance = y-troop[num].y ;// i
            //printf("%d\n", distance);// %
            if (distance == 0 || x != troop[num].x){return 0;}
            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++){
                if (distance < 1)   {k = i*-1;}else{k = i;}
                if (Board[k+troop[num].y][x] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+troop[num].y][x])))
                    {
                        return 1;
                    }
                    else{ return 0;}
                }
            }
            return 1;
            
        }
    }
    
    else if ((num==2)||(num==3)||(num==4)||(num==22)||(num==23)||(num==24))//2-4 22-24 footman
    {
        if (troop[num].filp == 0){
            distance = abs(y-troop[num].y)+abs(x-troop[num].x);
            if (distance == 1){
                if ((Board[y][x]==0)||(Is_enemy(num,Board[y][x]))){
                    return 1;
                }
                else{return 0;}
            }
            else{return 0;}
        }
        else if ((troop[num].filp == 1)){
            if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1)) {
                if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
                {
                    return 1;
                }
                else{ return 0;}
            }
            else if ((((troop[num].y-y)==2)&&(x-troop[num].x==0)&&(Board[y-1][x]==0)))
            {
                return 1;
            }
            else{return 0;}
        }
    }
    else if ((num==5)||(num==6)||(num==7)||(num==25)||(num==26)||(num==27))//5-7, 25-27 = PikeMan 
    {
        if ((troop[num].filp == 0))
        { if (abs(x-troop[num].x) > 2)return 0;
            if (((y-troop[num].y<0)&&(abs(x-troop[num].x)>0)&&((troop[num].y-y)==abs(x-troop[num].x))))
            {
                return 1;
            }
        }
        else if ((troop[num].filp == 1))
        {
            if ((abs(y-troop[num].y)==1)&&((x-troop[num].x)==0))
            {
                return 1;
            }
            else if ((((y-troop[num].y)==2)&&(x-troop[num].x)==0)&&(Board[y-1][x]==0))
            {
                return 1;
            }
        }
    }/*
    else if ((num==8)||(num==28))//8,28 = Assassin
    {
        if ((troop[num].filp == 0))
        {

            if ( (((disx)==0)&&(disy<=-2)) || ((abs(disx)>=2)&&((disy)>=2)&&(abs(disx)==abs(disy))))
            {return 1;/*
                if (((x-troop[num].x)>0)&&(Board[tny+1][tnx+1]==0)){return 1;}
                else if (((x-troop[num].x)==0)&&(Board[tny-1][tnx]==0)){return 1;}
                else if (((x-troop[num].x)<0)&&(Board[tny+1][tnx-1]==0)){return 1;  }
            }
        }
        else if ((troop[num].filp == 1))
        {
            if ( (((disx)==0)&&(disy>=2)) || ((abs(disx)>=2)&&((disy)<=-2)&&(abs(disx)==abs(disy))))
            {return 1; /*
                if (((x-troop[num].x)>0)&&(Board[tny-1][tnx-1]==0)){return 1;}
                else if (((x-troop[num].x)==0)&&(Board[tny+1][tnx]==0)){return 1;}
                else if (((x-troop[num].x)<0)&&(Board[tny-1][tnx+1]==0)){return 1;  }
            }
        }
    } */
    else if ((num== 8)||(num==28 ))//  9,29 = Bowman
    {
        if ((troop[num].filp == 0))
        {
            distance = abs(y-troop[num].y)+abs(x-troop[num].x);
            if ((distance == 1)&&(disy!=1))
            {
                return 1;
            }
            else if ((distance == 2)&&((abs(disx)==2)||(disy==2)))
            {
                return 1;
            }
        }
        else if ((troop[num].filp == 1))
        {
            if (((y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))    {
                if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
                {
                    return 1;
                }
            }
            else if ((disx == 0)&&(disy == -1))
            {
                return 1;
            }
        }
    }
    else if ((num== 9)||(num==29 ))//  = champion
    {   distance = abs(y-troop[num].y)+abs(x-troop[num].x);
        if ((troop[num].filp == 0))
        {
            
            if ((distance == 1))
            {
                return 1;
            }
            else if ((distance == 2)&&((abs(disx)==2)||abs(disy)==2))
            {
                return 1;
            }
        }
        else if ((troop[num].filp == 1))
        {
            if ((distance == 2)&&((abs(disx)==2)||abs(disy)==2))
            {
                return 1;
            }
        }
    }
    else if ((num== 10)||(num==30 ))// = Ranger
    {
        if ((troop[num].filp == 0))
        {
            if (((distance == 3)&&(disy<0))&&((disy==-2)||abs(disx)==2)){return 1;}
            distance = abs( y-troop[num].y) ;// i
            //printf("%d\n", distance);// %
            if (x != troop[num].x){return 0;}
            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++){
                if (distance < 1)   {k = i*-1;}else{k = i;}
                if (Board[k+troop[num].y][x] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+troop[num].y][x])))
                    {
                        return 1;
                    }
                    else{ return 0;}
                }
            }
            return 1;
        }
    
    
    /*Gragoon
        if ((troop[num].filp == 0)&&(distance == 1)&&(disy==0))
        {return 1;}
        else if ((troop[num].filp == 1))
        {if ((y-troop[num].y==-1)&&((x-troop[num].x)==0))
            {
                return 1;
            }
            else if ((((y-troop[num].y)==-2)&&(x-troop[num].x)==0)&&(Board[y-1][x]==0))
            {
                return 1;
            }
            else if (disy==abs(disx))
            {ABSdis = abs(disy);
            for (i = 1; i <= ABSdis; i++){
                if (disx < 1)   {k = i*-1;}else{k = i;}
                if (Board[k+tny][k+tnx] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+tny][k+tnx])))
                    {return 1;  }
                    else{ return 0;}
                }
            }
            return 1;
            }
            else if ((y-troop[num].y==-2)&&(abs(x-troop[num].x)==1)){return 1;  }
        }
    }*/

    else if ((num== 11)||(num==31 ))//12,32 = General
    {
        if ((troop[num].filp == 0))
        {
            if((distance == 1)&&(disx==0)){return 1;}
            else if (((distance == 2)&&(disy==0))&&(Board[abs(y-tny)/2][tnx]==0)){return 1;}
            else if ((abs(x-tnx)==1)&&((y-tny)==-2)){return 1;} 
        }
        else if ((troop[num].filp == 1))
        {   if ((abs(x-tnx)==1)&&((y-tny)==-2)){return 1;}
            else if (((distance == 2)&&(disy==0))&&(Board[abs(y-tny)/2][tnx]==0)){return 1;}
            else if ((distance == 1)&&(disy!=1)){return 1;}
            
        }
    }
    else if ((num== 12)||(num==32 ))//13, 34 = knight
    {
        if ((troop[num].filp == 0))
        {
            if (((distance == 2)&&(disy==2))&&(Board[y-1][tnx]==0)){return 1;}
            else if ((distance == 1)&&(disy!=-1)){return 1;}
            else if ((abs(x-tnx)==1)&&((y-tny)==-2)){return 1;} 
        }
        else if ((troop[num].filp == 1))
        {
            if (((y-tny>0)&&(abs(x-tnx)>0)&&(abs(tny-y)==abs(x-tnx))))
            {   return 1;   }
            distance = y-troop[num].y ;// i
            //printf("%d\n", distance);// %
            if (distance >= 0 || x != troop[num].x){return 0;}
            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++){
                if (distance < 1)   {k = i*-1;}else{k = i;}
                if (Board[k+troop[num].y][x] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+troop[num].y][x])))
                    {
                        return 1;
                    }
                    else{ return 0;}
                }
            }
            return 1;

        }
    }
    else if ((num== 13)||(num== 33 ))// = Marshall
    {
        if ((troop[num].filp == 0))
        {if(disy==0){distance = x-troop[num].x ;            
            if (distance == 0 || y != troop[num].y){return 0;}
            ABSdis = abs(distance);             
            for (i = 1; i <= ABSdis; i++){
                if (distance < 1)   {k = i*-1;}else{k = i;}
                if (Board[y][k+troop[num].x] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[y][k+troop[num].x])))
                    {
                        return 1;
                    }
                    else{ return 0;}
                }
            }
            return 1;}
        else if ((disy == -2&&abs(disx)==2)||(disy == 2&&disx== 0)){return 1;}
        }
        else if ((troop[num].filp == 1))
        {
            if (((distance == 2)&&(disy==0))&&(Board[abs(y-tny)/2][tnx]==0)){return 1;}
            else if ((distance == 1)&&(disy!=1)){return 1;}
            if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1)) {
                if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
                {return 1;}
                else{ return 0;}
            }
        }
    }
    else if ((num== 14)||(num==34 ))// = Seer
    {
        if ((troop[num].filp == 0))
        {
            if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1)) {
                if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
                {return 1;}}
            else if (((abs(y-troop[num].y)==2)&&(abs(x-troop[num].x)==0))||((abs(x-troop[num].x)==2)&&abs(y-troop[num].y)==0))
            {return 1;}
        }
        else if ((troop[num].filp == 1))
        { if (abs(disx)+abs(disy) == 1){return 1;}
        else if (((abs(tny-y)+abs(tny-y))==4)&&((abs(tny-y)==2)&&(abs(tnx-x)==2))){return 1;}
        }
    
    }
    else if ((num== 15)||(num==15 ))//  Priest
    {
        if ((troop[num].filp == 0))
        {if (abs(disy)==abs(disx))
            {ABSdis = abs(disy);
            for (i = 1; i <= ABSdis; i++){
                if (disx < 1)   {k = i*-1;}else{k = i;}
                if (Board[k+tny][k+tnx] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+tny][k+tnx])))
                    {return 1;  }
                    else{ return 0;}
                }
            }
            return 1;
            }
        }
        else if ((troop[num].filp == 1))
        {if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))    {
                if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
                {return 1;}}
        else if (((abs(tny-y)+abs(tny-y))==4)&&((abs(tny-y)==2)&&(abs(tnx-x)==2))){return 1;}
        }
        }
    
        else if ((troop[num].filp == 1))
        {
            //else if ((((y-troop[num].y)==-2)&&(x-troop[num].x)==0)&&(Board[y-1][x]==0))   return 1;
            if ((disy)==abs(disx)*-1)
            {ABSdis = abs(disy);
            for (i = 1; i <= ABSdis; i++){
                if (disx < 1)   {k = i*-1;}else{k = i;}
                if (Board[k+tny][k+tnx] != 0)
                {
                    if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+tny][k+tnx])))
                    {return 1;  }
                    else{ return 0;}
                }
            }
            return 1;
            }
            else if ((y-troop[num].y==2)&&(abs(x-troop[num].x)==1)){return 1;}
            }
    }
    else if ((num== 16)||(num==36 ))//11,31 = Jester
    {
        if ((troop[num].filp == 0))
        {if (((y-tny)==-1)&&(abs(disx)==1) )return 1;
        else if ((((y-troop[num].y)==2)&&(x-troop[num].x)==0)&&(Board[y-1][x]==0))return 1;
        else if ((distance == 3)&&((disy)==2||abs(disx)==2)&&(Board[y][abs(x-tnx)/2]==0)&&(y>1))return 1;
         }

        else if ((troop[num].filp == 1))
        {if ((((y-tny)==-1)&&(abs(disx)==1)) || (((y-tny)==1)&&(abs(disx)==0)))return 1;
        else if (abs(x-troop[num].x) > 2)return 0;
        else if (((y-troop[num].y>0)&&(abs(x-troop[num].x)>0)&&((y-troop[num].y)==abs(x-troop[num].x))))return 1;
        }
    }
    else if ((num== 17)||(num==37 ))//18, 38 wizard
    {
        if ((troop[num].filp == 0))
        {if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))    
            {
                if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
                {return 1;}
                else{ return 0;}
            }
        else if (distance == 1){return 1;}
        }
        else if ((troop[num].filp == 1))
        {if (((abs(tny-y)+abs(tnx-x))==4)&&((abs(tny-y)==2)&&(abs(tnx-x)==2))){return 1;}
        else if (((abs(y-troop[num].y)==2)&&(abs(x-troop[num].x)==0))||((abs(x-troop[num].x)==2)&&abs(y-troop[num].y)==0))
            {return 1;}
        }
    }
    
    return 0;
}
