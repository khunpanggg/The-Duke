/*******************************************************************************************
 *
 *   The Duke
 *
 *   The boardgame write in pure C with raylib library
 *
 *   Copyright (c) 2019 (@dukes03, @Icyscools, @khunpanggg, @chrittima)
 *
 ********************************************************************************************/

#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

const int screenWidth = 800;
const int screenHeight = 640;

int Board[6][6]; // Y X
void setupboard(Texture2D scarfy, Texture2D board_pic); //ไว้เริ่มเล่นset upเกม
void viewboradnow(); //ปริ้นกระดาษให้ดู
void movetroop(int x1, int y1, int x2, int y2); //เดิน กะ กิน เสด1ตัว
int summon(int p); //สุ่มเรียกตัวละคร ยังไม่เสด
void setup_troop_pic(); //ตั้งเเค่ตัวละคร
void viewboradnum(); //ดูรหัสตัวละครบนกระดาน
void filp_troop(int i); //กลับด้านตัวละคร
void SetColor(int ForgC); //ตั้งค่าสีตัวอักษร
int CanMove(int num, int x, int y);
void CanMove_map(int x, int y); //ฟังก์ชั่นเช็คว่าตัวนั้นเดินไปได้ไหม (ข้อมูลการเดินทั้งหมดอยู่ตรงนั้น)
void rotateBoard(); //หมุนกระดาน
int checkCheckmate(int on_player); //เช็กว่าตอนนี้ player checkmate ไหม
int checkLose(int on_player); //เช็กว่าแพ้รึยัง ในรอบของเรา
void drawMenu(); // Draw menu
void drawGameboard(Texture2D scarfy, Texture2D board_pic); // Draw game board

struct Troop {
    int x;
    int y;
    bool isAlive;
    int left; //เหลือกี่่ตัว
    int filp;
}
troop[41]; //สร้างไว้คราวๆก่อน 1-20 p1 21-40 p2   1เเละ21 เป็นDuke 0เป็นช่องว่าง

Vector2 mousePoint;
Vector2 position = {
    90.0f,
    70.0f
};
Image troop_image;
Texture2D scarfy;
int page = 0; // 0 is menu, 1 is game board, 2 is how to
int troop_tie = 1;
int setup_board = 0, SET_duke = 0, player = 0, selecty = 99, selectx = 99, newtroop = 0;
int summonint = 0;
int main() {
    // Initialization
    //--------------------------------------------------------------------------------------

    double playingTime = 0;
    char testString[100];

    InitWindow(screenWidth, screenHeight, "The Duke");
    Image background = LoadImage("resources/background.png");
    Image dukelogo = LoadImage("resources/dukelogo.png");
    Texture2D logo = LoadTextureFromImage(dukelogo);
    Texture2D texture = LoadTextureFromImage(background);

    bool selected[37] = {
        false
    };
    SetWindowIcon(dukelogo);
    SetTargetFPS(60);

    Image image = LoadImage("resources/board.png");
    ImageResize( & image, screenWidth, screenHeight);
    Texture2D board_pic = LoadTextureFromImage(image);

    troop_image = LoadImage("resources/Troop.png"); // Texture loading
    ImageResize( & troop_image, 7520, 95 * 0.9);
    scarfy = LoadTextureFromImage(troop_image);

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
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
            } else {
                drawGameboard(scarfy, board_pic);
            }

        } else if (page == 2) {
            drawHowTo();
        }

        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

void drawMenu(Texture2D texture, Texture2D logo) {
    BeginDrawing();

    ClearBackground(LIGHTGRAY);
    DrawText("The Duke", screenWidth / 2 - (15 * strlen("The Duke")), screenHeight / 4, 50, RAYWHITE);
    DrawTexture(logo, 0, 0, RED);
    DrawTexture(texture, 0, 0, RED);

    mousePoint = GetMousePosition();
    Rectangle menuRecs[3];
    for (int i = 0; i < 3; i++) {
        menuRecs[i].x = screenWidth / 3;
        menuRecs[i].y = screenHeight * (2 + (i * 0.5)) / 4;
        menuRecs[i].width = 300;
        menuRecs[i].height = 50;
    }

    for (int i = 0; i < 3; i++) // Iterate along all the rectangles
    {
        if (CheckCollisionPointRec(mousePoint, menuRecs[i])) {
            DrawRectangle(screenWidth / 3, screenHeight * (2 + (i * 0.5)) / 4, 300, 50, RED);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                page = i + 1;
                setup_board = 0, SET_duke = 0, player = 0, selecty = 99, selectx = 99;
            }
        } else DrawRectangle(screenWidth / 3, screenHeight * (2 + (i * 0.5)) / 4, 300, 50, GRAY);
    }

    DrawText("Start", screenWidth / 3 + 125, screenHeight * 2 / 4 + 12, 25, RAYWHITE);
    DrawText("How to play", screenWidth / 3 + 90, screenHeight * 2.5 / 4 + 12, 25, RAYWHITE);
    DrawText("Exit", screenWidth / 3 + 125, screenHeight * 3 / 4 + 12, 25, RAYWHITE);

    EndDrawing();
}

void drawGameboard(Texture2D scarfy, Texture2D board_pic) {
    Vector2 mousePoint;
    Rectangle hitbox_onboard[37];
    Rectangle summonbox = {
        screenWidth / 4 + 80,
        screenHeight * 3 / 4 + 90,
        190,
        50
    };

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            int n = (i * 6) + j;
            hitbox_onboard[n].x = 85 + (j * scarfy.width / 76 + 5 * j);
            hitbox_onboard[n].y = 68.0f + (i * scarfy.height - i * 2);
            hitbox_onboard[n].width = scarfy.width / 76 + 6;
            hitbox_onboard[n].height = scarfy.height - 2;
        }
    }

    Rectangle frameRec = {
        0.0f,
        0.0f,
        (float) scarfy.width / 76,
        (float) scarfy.height
    };
    //frameRec.x = (2*1 + 1)*(float)scarfy.width/76;
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawTexture(board_pic, 0, 0, WHITE);
    //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) troop_tie += 1;
    //DrawTextureRec(scarfy, frameRec, position, WHITE);
    mousePoint = GetMousePosition();
    if (CheckCollisionPointRec(mousePoint, summonbox) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && summonint == 0) {
        newtroop = summon(player);
        summonint = 1;
        //DrawRectangle(screenWidth / 4+40, screenHeight *3/ 4+ 90, 190, 50,RED);
    }

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            int n = (i * 6) + j;
            troop[Board[i][j]].x = j;
            troop[Board[i][j]].y = i;
            Vector2 position = {
                85 + (j * scarfy.width / 76 + 5 * j),
                68.0f + (i * scarfy.height - i * 2)
            }; //จัดใหม่
            frameRec.x = (2 * Board[i][j] + troop[Board[i][j]].filp) * (float) scarfy.width / 76;
            DrawTextureRec(scarfy, frameRec, position, WHITE);
            mousePoint = GetMousePosition();

            if (selectx + selecty != 198) // Click on something
            {
                /*if (Can_Strike(Board[selecty][selectx], j,i))
                {
                    DrawRectangle(85+ (j*scarfy.width/76+5*j+scarfy.width/76/2),68.0f +(i*scarfy.height-i*2+scarfy.height/2), 10, 10, BLUE);
                    printf("1111111\n");
                }*/
                if (Can_summon(player, Board[selecty][selectx])) {
                    DrawRectangle(screenWidth / 4 + 80, screenHeight * 3 / 4 + 90, 190, 50, BROWN);
                    DrawText("Summon", screenWidth / 4 + 100, screenHeight * 3 / 4 + 100, 40, RAYWHITE);
                }

                if (CanMove(Board[selecty][selectx], j, i) && summonint == 0) {
                    DrawRectangle(85 + (j * scarfy.width / 76 + 5 * j + scarfy.width / 76 / 2), 68.0f + (i * scarfy.height - i * 2 + scarfy.height / 2), 10, 10, RED);
                    DrawText(FormatText("x%i y%i ", j, i), 85 + (j * scarfy.width / 76 + 5 * j + scarfy.width / 76 / 2), 68.0f + (i * scarfy.height - i * 2 + scarfy.height / 2), 25, LIGHTGRAY);
                }
            }

            if (CheckCollisionPointRec(mousePoint, hitbox_onboard[n])) {
                if (((Board[i][j] >= 21 && player == 1) || (Board[i][j] < 21 && player == 0)) && Board[i][j] != 0) {
                    DrawRectangle(85 + (j * scarfy.width / 76 + 5 * j), 68.0f + (i * scarfy.height - i * 2), scarfy.width / 76 / 8 + 6, scarfy.height / 8 - 2, BLUE);
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //ถ้าเมาส์คลิกซ้าย
                    {
                        selectx = j;
                        selecty = i;
                    }
                } else if (selectx + selecty != 198 && CanMove(Board[selecty][selectx], j, i) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && summonint == 0) {
                    movetroop(selectx, selecty, j, i);
                    if (player == 1) {
                        player = 0;
                        selectx = 99;
                        selecty = 99;
                    } else {
                        player = 1;
                        selectx = 99;
                        selecty = 99;
                    }

                    rotateBoard();
                } else if (summonint == 1) // If player already click on summon
                {
                    int pnum = player * 20 + 1;

                    if ((abs(troop[pnum].x - j) + abs(troop[pnum].y - i)) == 1 && (Board[i][j] == 0)) {
                        Rectangle frameR = {
                            0.0f,
                            0.0f,
                            (float) scarfy.width / 76,
                            (float) scarfy.height
                        };
                        frameR.x = (2 * newtroop) * (float) scarfy.width / 76;
                        DrawTextureRec(scarfy, frameR, position, WHITE);
                        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                            Board[i][j] = newtroop;
                            leftout(newtroop);
                            troop[newtroop].x = j;
                            troop[newtroop].y = i;
                            summonint = 0;
                            rotateBoard();
                            if (player == 1) {
                                player = 0;
                                selectx = 99;
                                selecty = 99;
                            } else {
                                player = 1;
                                selectx = 99;
                                selecty = 99;
                            }
                        }
                    }
                }
                //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) page = i+1;(scarfy, frameRec, position, WHITE
            }
            //else DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);
        }
    }
    //DrawTextureEx(scarfy, Vector2 position, float rotation, float scale, Color tint);
    DrawText(FormatText("player%i select_id = %d", player, Board[selecty][selectx]), 10, 40, 20, RED);
    if (newtroop) {
        DrawText(FormatText("New troop id %i", newtroop), 10, screenHeight - 40, 20, LIGHTGRAY);
    }
    EndDrawing();
}

void drawHowTo() {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);
    DrawRectangle(screenWidth / 2 - 250, screenHeight / 2 - 250, 500, 500, BLACK);
    DrawRectangle(screenWidth / 2 - 242.5, screenHeight / 2 - 242.5, 485, 485, RAYWHITE);

    DrawText("How To Play", screenWidth / 2 - 85, screenHeight / 2 - 220, 30, BLACK);
    Rectangle menuNext[3];
    mousePoint = GetMousePosition();
    for (int i = 0; i < 3; i++) {
        menuNext[i].x = 170 + (i * 200);
        menuNext[i].y = 490;
        menuNext[i].width = 60;
        menuNext[i].height = 60;
    }

    for (int i = 0; i < 3; i++) // Iterate along all the rectangles
    {
        if (CheckCollisionPointRec(mousePoint, menuNext[i])) {
            if (i == 0) {
                DrawRectangle(menuNext[i].x, menuNext[i].y, 60, 60, RED);
                DrawText("<", menuNext[i].x + 25, menuNext[i].y - 4, 75, BLACK);

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    DrawText("Pang NIchapat", menuNext[i].x + 25, menuNext[i].y - 4, 25, BLACK);
                }
            }
            if (i == 1) {
                DrawRectangle(menuNext[i].x - 5, menuNext[i].y, 100, 60, RED);
                DrawText("Home", menuNext[i].x + 12, menuNext[i].y + 14, 30, BLACK);

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    page = 0;
                }
            }
            if (i == 2) {
                DrawRectangle(menuNext[i].x, menuNext[i].y, 60, 60, RED);
                DrawText(">", menuNext[i].x + 25, menuNext[i].y - 4, 75, BLACK);

                if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                    page = 0;
                }
            }
        } else if (i == 0) {
            DrawRectangle(menuNext[i].x, menuNext[i].y, 60, 60, GRAY);
            DrawText("<", menuNext[i].x + 25, menuNext[i].y - 4, 75, BLACK);
        } else if (i == 1) {
            DrawRectangle(menuNext[i].x - 5, menuNext[i].y, 100, 60, GRAY);
            DrawText("Home", menuNext[i].x + 12, menuNext[i].y + 14, 30, BLACK);
        } else if (i == 2) {
            DrawRectangle(menuNext[i].x, menuNext[i].y, 60, 60, GRAY);
            DrawText(">", menuNext[i].x + 25, menuNext[i].y - 4, 75, BLACK);
        }
    }
    EndDrawing();
}

void leftout(int i) {
    if (troop[i].left != 0) {
        troop[i].left -= 1;
    }
}

void movetroop(int x1, int y1, int x2, int y2) {
    Board[y2][x2] = Board[y1][x1];
    Board[y1][x1] = 0;
    filp_troop(Board[y2][x2]);
}

void filp_troop(int k) {
    if (troop[k].filp == 1) {
        troop[k].filp = 0;
    } else {
        troop[k].filp = 1;
    }
}

int Can_summon(int p, int trop) {
    if ((trop == 21) && ((p == 1))) {
        for (int y = 0; y < 6; y++) {
            for (int x = 0; x < 6; x++) {
                if ((abs(troop[p].x - x) + abs(troop[p].y - y)) != 1 && Is_ally(troop[p], Board[y][x]) != 1) {
                    return 1;
                }
            }
        }

    } else if ((trop == 1) && ((p == 0))) {
        for (int y = 0; y < 6; y++) {
            for (int x = 0; x < 6; x++) {
                if ((abs(troop[p].x - x) + abs(troop[p].y - y)) != 1 && Is_ally(troop[p], Board[y][x]) != 1) {
                    return 1;
                }
            }
        }
    } else {
        return 0;
    }
}

int summon(int p) {
    int x = 99, y = 99, pl = 20 * (p) + 1, re = 0;
    while (troop[re].left == 0) {
        if (p == 0) {
            re = rand() % 18;
        } else {
            re = (rand() % 18) + 21;
        }

    }
    return player ? 35 : 15;
}

int Is_ally(int numA, int numB) {
    if ((numA >= 21) && ((numB >= 21))) {
        return 1;
    } else if (((numA < 21) && (numA != 0)) && ((numB < 21) && (numB != 0))) {
        return 1;
    } else {
        return 0;
    }
}

int Is_enemy(int numA, int numB) {
    if ((numA >= 21) && ((numB < 21) && (numB != 0))) {
        return 1;
    } else if ((numB >= 21) && ((numA < 21) && (numA != 0))) {
        return 1;
    } else {
        return 0;
    }
}

void CanMove_map(int x, int y) {
    int i, j;
    for (i = 0; i <= 5; i++) {
        for (j = 0; j <= 5; j++) {
            if (CanMove(Board[y][x], j, i) != 0) {
                /**/
            }
            //else if((i==y)&&(j==x)){if (troop[Board[y][x]].filp == 0){printf("i ");}
            //else if (troop[Board[y][x]].filp == 1){printf("I ");} 
        }
        //else{printf("- ");}
        //if (j == 5) {printf(" %d \n", i);}
    }
}

void setupboard(Texture2D scarfy, Texture2D board_pic) {
    srand(time(NULL));
    int i, j, ans = 0, jjj = 3, p = 21;
    for (i = 0; i <= 5; i++) {
        for (j = 0; j <= 5; j++) {
            Board[i][j] = 0;
        }
    }

    for (i = 1; i <= 41; i++) {
        troop[i].left = 1;
        troop[i].filp = 0;
    }

    Board[0][1] = 0; //Bug

    while ((SET_duke != 5)) {
        Vector2 mousePoint;
        Rectangle hitbox_onboard[37];
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                int n = (i * 6) + j;
                hitbox_onboard[n].x = 85 + (j * scarfy.width / 76 + 5 * j);
                hitbox_onboard[n].y = 68.0f + (i * scarfy.height - i * 2);
                hitbox_onboard[n].width = scarfy.width / 76 + 6;
                hitbox_onboard[n].height = scarfy.height - 2;
            }
        }

        Rectangle frameRec = {
            0.0f,
            0.0f,
            (float) scarfy.width / 76,
            (float) scarfy.height
        };
        frameRec.x = (2 * 1) * (float) scarfy.width / 76;
        BeginDrawing();
        ClearBackground(LIGHTGRAY);
        DrawTexture(board_pic, 0, 0, WHITE);
        //if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) troop_tie += 1;
        if (SET_duke == 0) DrawText("Player 1\nPlan The Duke", screenWidth / 3, screenHeight / 2, 50, RAYWHITE); //จัดใหม่
        if (SET_duke == 1 || SET_duke == 4) DrawText("Player 2\nPlan Footman", screenWidth / 2.5, screenHeight / 4, 50, BLACK);
        if (SET_duke == 2 || SET_duke == 3) DrawText("Player 1\nPlan Footman", screenWidth / 3, screenHeight / 2, 50, RAYWHITE);

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                int n = (i * 6) + j;
                troop[Board[i][j]].x = j;
                troop[Board[i][j]].y = i;
                mousePoint = GetMousePosition();
                if (CheckCollisionPointRec(mousePoint, hitbox_onboard[n])) { //ถ้าเมาส์อยู่ในช่อง
                    Vector2 position = {
                        85 + (j * scarfy.width / 76 + 5 * j),
                        68.0f + (i * scarfy.height - i * 2)
                    };
                    if (SET_duke == 0) { //วาง Duke
                        if (n == 33 || n == 32) {
                            DrawRectangle(85 + (j * scarfy.width / 76 + 5 * j), 68.0f + (i * scarfy.height - i * 2), scarfy.width / 8 / 76 + 6, scarfy.height / 8 - 2, BLUE);

                            DrawTextureRec(scarfy, frameRec, position, WHITE); //หมากขาว

                            frameRec.x = (2 * 21) * (float) scarfy.width / 76;
                            if (n == 33) {
                                jjj = 2;
                            } else {
                                jjj = 3;
                            }
                            Vector2 positionn = {
                                85 + (jjj * scarfy.width / 76 + 5 * jjj),
                                68.0f + (0 * scarfy.height - 0 * 2)
                            };
                            DrawTextureRec(scarfy, frameRec, positionn, WHITE); //หมากดำ
                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //ถ้าเมาส์คลิกซ้าย
                            {
                                // Set Duke
                                SET_duke = 1;
                                ans = n;
                                Board[5][ans - 30] = 1;
                                leftout(1);
                                if (ans == 33) {
                                    Board[0][2] = 21;
                                } else {
                                    Board[0][3] = 21;
                                }
                                leftout(21);
                            }
                        }
                    }

                    if (SET_duke == 1 || SET_duke == 4) {
                        frameRec.x = (2 * 22) * (float) scarfy.width / 76;
                        if ((abs(troop[21].x - j) + abs(troop[21].y - i)) == 1 && (Board[i][j] == 0)) {
                            DrawTextureRec(scarfy, frameRec, position, WHITE);
                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //ถ้าเมาส์คลิกซ้าย
                            {
                                p = 1;
                                if (SET_duke == 1) {
                                    Board[i][j] = 22;
                                    leftout(22);
                                    SET_duke = 2;
                                } else if (SET_duke == 4) {
                                    Board[i][j] = 23;
                                    leftout(23);
                                    SET_duke = 5;
                                }
                            }
                        }
                    }

                    if (SET_duke == 2 || SET_duke == 3) {
                        frameRec.x = (2 * 2) * (float) scarfy.width / 76;
                        if ((abs(troop[1].x - j) + abs(troop[1].y - i)) == 1 && (Board[i][j] == 0)) {
                            DrawTextureRec(scarfy, frameRec, position, WHITE);
                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) //ถ้าเมาส์คลิกซ้าย
                            {
                                if (SET_duke == 2) {
                                    Board[i][j] = 2; // Set troop
                                    leftout(2);
                                    SET_duke = 3;
                                    p = 1;
                                } else if (SET_duke == 3) {
                                    Board[i][j] = 3; // Set troop
                                    leftout(3);
                                    SET_duke = 4;
                                    p = 21;
                                }
                            }
                        }
                    }
                }

                if (SET_duke == 1 || SET_duke == 4) {
                    Vector2 posi = {
                        85 + (j * scarfy.width / 76 + 5 * j),
                        68.0f + (i * scarfy.height - i * 2)
                    }; //จัดใหม่
                    frameRec.x = (2 * Board[i][j]) * (float) scarfy.width / 76;
                    DrawTextureRec(scarfy, frameRec, posi, WHITE);
                    if (((abs(troop[21].x - j) + abs(troop[21].y - i)) == 1) && (Board[i][j] == 0)) {
                        DrawRectangle(85 + (j * scarfy.width / 76 + 5 * j), 68.0f + (i * scarfy.height - i * 2), 10, 10, BLUE);
                    }
                } else if (SET_duke == 2 || SET_duke == 3) {
                    Vector2 posi = {
                        85 + (j * scarfy.width / 76 + 5 * j),
                        68.0f + (i * scarfy.height - i * 2)
                    }; //จัดใหม่
                    frameRec.x = (2 * Board[i][j]) * (float) scarfy.width / 76;
                    DrawTextureRec(scarfy, frameRec, posi, WHITE);
                    if (((abs(troop[1].x - j) + abs(troop[1].y - i)) == 1) && (Board[i][j] == 0)) {
                        DrawRectangle(85 + (j * scarfy.width / 76 + 5 * j), 68.0f + (i * scarfy.height - i * 2), 10, 10, BLUE);
                    }
                }
                //else DrawRectangle(85+ (j*scarfy.width/76+5*j),68.0f +(i*scarfy.height-i*2), scarfy.width/76+6, scarfy.height-2, WHITE);
            }
        }

        EndDrawing();
    }

    setup_board += 1;
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

    ImageFlipVertical( & troop_image);
    scarfy = LoadTextureFromImage(troop_image);
}

int checkCheckmate(int on_player) {
    struct Troop dukeTroop = troop[(on_player * 20) + 1];
    int startTroop = (!on_player * 20) + 1;
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 6; x++) {
            int tr = Board[y][x];
            if (tr >= startTroop && tr <= startTroop + 20 && tr != 0) {
                if (CanMove(tr, dukeTroop.x, dukeTroop.y)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int checkLose(int on_player) {
    int ownDuke = (on_player * 20) + 1;
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 6; x++) {
            int tr = Board[y][x];
            if (tr == ownDuke) {
                return 0;
            }
        }
    }
    return 1;
}
int Can_Command(int num, int x1, int y1, int x2, int y2) {
    if (!Is_ally(num, Board[y1][x1])) {
        return 0;
    } else if (Board[y1][x1] == 0) {
        return 0;
    } else if (Is_ally(Board[y2][x2], Board[y1][x1])) {
        return 0;
    } else if ((num == 11) || (num == 31)) //12,32 = General
    {
        if (((troop[num].y - y1 == -1) && abs(troop[num].x - x1) <= 1) && abs(troop[num].x - x1) == 1) {
            return 1;
        }
    } else if (((num == 13) || (num == 33)) && abs(troop[num].x - x1) == 1) // = Marshall
    {
        if ((troop[num].y - y1 == 1) && abs(troop[num].x - x1) <= 1) {
            return 1;
        }
    }
}

int Can_Strike(int num, int x, int y) {
    if (Is_ally(num, Board[y][x])) {
        return 0;
    } else if (Board[y][x] == 0) {
        return 0;
    } else if ((((num == 5) || (num == 6) || (num == 7) || (num == 25) || (num == 26) || (num == 27)))) {
        if ((troop[num].y - y == 2) && abs(troop[num].x - x) == 1) {
            return 1;
        }
    } else if (((num == 9) || (num == 29)) && troop[num].filp == 1) {
        if (abs(troop[num].y - y == 2) + abs(troop[num].x - x) == 1) {
            return 1;
        }
    } else if (((num == 8) || (num == 28)) && troop[num].filp == 1) {
        if (((troop[num].y - y == 2) && abs(troop[num].x - x) == 0) || ((troop[num].y - y == 1) && abs(troop[num].x - x) == 1)) {
            return 1;
        }
    }
    return 0;
}

int CanMove(int num, int x, int y) {
    /*
        1,21 = Duke
        2-4,22-24 = Footman
        5-7, 25-27 = PikeMan
        8, 28 = Assassin
        9, 29 = Bowman
        10, 30 = Champion
        11, 31 = Gragoon
        12, 32 = General
        14, 34  == Knight
        15, 35 == Marsall
     */
    int i, j, k, distance, ABSdis, disx, disy, tnx = troop[num].x, tny = troop[num].y;
    //if (num >= 21) y = abs(5-y);
    disx = x - troop[num].x;
    disy = y - troop[num].y;
    distance = abs(disy) + abs(disx);
    if (Is_ally(num, Board[y][x])) {
        return 0;
    }

    if (num == 1 || num == 21) //Duke    
    {
        if (troop[num].filp == 0) {
            distance = x - troop[num].x;
            if (distance == 0 || y != troop[num].y) {
                return 0;
            }

            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++) {
                if (distance < 1) {
                    k = i * -1;
                } else {
                    k = i;
                }

                if (Board[y][k + troop[num].x] != 0) {
                    if ((abs(k) == ABSdis) && (Is_enemy(num, Board[y][k + troop[num].x])) && troop[num].filp == 1) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            return 1;
        } else if (troop[num].filp == 1) {
            distance = y - troop[num].y;
            if (distance == 0 || x != troop[num].x) {
                return 0;
            }

            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++) {
                if (distance < 1) {
                    k = i * -1;
                } else {
                    k = i;
                }

                if (Board[k + troop[num].y][x] != 0) {
                    if ((abs(k) == ABSdis) && (Is_enemy(num, Board[k + troop[num].y][x]))) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            return 1;
        }
    } else if ((num == 2) || (num == 3) || (num == 4) || (num == 22) || (num == 23) || (num == 24)) //2-4 22-24 footman
    {
        if (troop[num].filp == 0) {
            distance = abs(y - troop[num].y) + abs(x - troop[num].x);
            if (distance == 1) {
                if ((Board[y][x] == 0) || (Is_enemy(num, Board[y][x]))) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else if (troop[num].filp == 1) {
            if ((abs(y - troop[num].y) == 1) && (abs(x - troop[num].x) == 1)) {
                if (((Board[troop[num].y][x] == 0) || (Board[y][troop[num].x] == 0))) {
                    return 1;
                }
            } else if ((((troop[num].y - y) == 2) && (x - troop[num].x == 0) && (Board[y + 1][x] == 0))) {
                return 1;
            }
        }
    } else if ((num == 5) || (num == 6) || (num == 7) || (num == 25) || (num == 26) || (num == 27)) //5-7, 25-27 = PikeMan 
    {
        if (troop[num].filp == 0) {
            if (abs(x - troop[num].x) > 2) return 0;
            if (((y - troop[num].y < 0) && (abs(x - troop[num].x) > 0) && ((troop[num].y - y) == abs(x - troop[num].x)))) {
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if ((abs(y - troop[num].y) == 1) && ((x - troop[num].x) == 0)) {
                return 1;
            } else if ((((y - troop[num].y) == 2) && (x - troop[num].x) == 0) && (Board[y - 1][x] == 0)) {
                return 1;
            }
        }
    }
    /*
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
    else if ((num == 8) || (num == 28)) //  9,29 = Bowman
    {
        if (troop[num].filp == 0) {
            distance = abs(y - troop[num].y) + abs(x - troop[num].x);
            if ((distance == 1) && (disy != 1)) {
                return 1;
            } else if ((distance == 2) && ((abs(disx) == 2) || (disy == 2))) {
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if (((y - troop[num].y) == 1) && (abs(x - troop[num].x) == 1)) {
                if (((Board[troop[num].y][x] == 0) || (Board[y][troop[num].x] == 0))) {
                    return 1;
                }
            } else if ((disx == 0) && (disy == -1)) {
                return 1;
            }
        }
    } else if ((num == 9) || (num == 29)) //  = champion
    {
        distance = abs(y - troop[num].y) + abs(x - troop[num].x);
        if (troop[num].filp == 0) {

            if ((distance == 1)) {
                return 1;
            } else if ((distance == 2) && ((abs(disx) == 2) || abs(disy) == 2)) {
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if ((distance == 2) && ((abs(disx) == 2) || abs(disy) == 2)) {
                return 1;
            }
        }
    } else if ((num == 10) || (num == 30)) // = Ranger
    {
        if (troop[num].filp == 0) {
            if (((distance == 3) && (disy < 0)) && ((disy == -2) || abs(disx) == 2)) {
                return 1;
            }
            distance = abs(y - troop[num].y); // i
            //printf("%d\n", distance);// %
            if (x != troop[num].x) {
                return 0;
            }
            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++) {
                if (distance < 1) {
                    k = i * -1;
                } else {
                    k = i;
                }

                if (Board[k + troop[num].y][x] != 0) {
                    if ((abs(k) == ABSdis) && (Is_enemy(num, Board[k + troop[num].y][x]))) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            return 1;
        } else if (troop[num].filp == 1) {

        }
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
    else if ((num == 11) || (num == 31)) //12,32 = General
    {
        if (troop[num].filp == 0) {
            if ((distance == 1) && (disx == 0)) {
                return 1;
            } else if (((distance == 2) && (disy == 0)) && (Board[abs(y - tny) / 2][tnx] == 0)) {
                return 1;
            } else if ((abs(x - tnx) == 1) && ((y - tny) == -2)) {
                return 1;
            }
        } else if ((troop[num].filp == 1)) {
            if ((abs(x - tnx) == 1) && ((y - tny) == -2)) {
                return 1;
            } else if (((distance == 2) && (disy == 0)) && (Board[abs(y - tny) / 2][tnx] == 0)) {
                return 1;
            } else if ((distance == 1) && (disy != 1)) {
                return 1;
            }
        }
    } else if ((num == 12) || (num == 32)) //13, 34 = knight
    {
        if (troop[num].filp == 0) {
            if (((distance == 2) && (disy == 2)) && (Board[y - 1][tnx] == 0)) {
                return 1;
            } else if ((distance == 1) && (disy != -1)) {
                return 1;
            } else if ((abs(x - tnx) == 1) && ((y - tny) == -2)) {
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if (((y - tny > 0) && (abs(x - tnx) > 0) && (abs(tny - y) == abs(x - tnx)))) {
                return 1;
            }
            distance = y - troop[num].y; // i
            //printf("%d\n", distance);// %
            if (distance >= 0 || x != troop[num].x) {
                return 0;
            }
            ABSdis = abs(distance);
            for (i = 1; i <= ABSdis; i++) {
                if (distance < 1) {
                    k = i * -1;
                } else {
                    k = i;
                }
                if (Board[k + troop[num].y][x] != 0) {
                    if ((abs(k) == ABSdis) && (Is_enemy(num, Board[k + troop[num].y][x]))) {
                        return 1;
                    } else {
                        return 0;
                    }
                }
            }
            return 1;

        }
    } else if ((num == 13) || (num == 33)) // = Marshall
    {
        if (troop[num].filp == 0) {
            if (disy == 0) {
                distance = x - troop[num].x;
                if (distance == 0 || y != troop[num].y) {
                    return 0;
                }

                ABSdis = abs(distance);
                for (i = 1; i <= ABSdis; i++) {
                    if (distance < 1) {
                        k = i * -1;
                    } else {
                        k = i;
                    }
                    if (Board[y][k + troop[num].x] != 0) {
                        if ((abs(k) == ABSdis) && (Is_enemy(num, Board[y][k + troop[num].x]))) {
                            return 1;
                        } else {
                            return 0;
                        }
                    }
                }
                return 1;
            } else if ((disy == -2 && abs(disx) == 2) || (disy == 2 && disx == 0)) {
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if (((distance == 2) && (disy == 0)) && (Board[abs(y - tny) / 2][tnx] == 0)) {
                return 1;
            } else if ((distance == 1) && (disy != 1)) {
                return 1;
            }
            if ((abs(y - troop[num].y) == 1) && (abs(x - troop[num].x) == 1)) {
                if (((Board[troop[num].y][x] == 0) || (Board[y][troop[num].x] == 0))) {
                    return 1;
                } else {
                    return 0;
                }
            }
        }
    } else if ((num == 14) || (num == 34)) // = Seer
    {
        if (troop[num].filp == 0) {
            if ((abs(y - troop[num].y) == 1) && (abs(x - troop[num].x) == 1)) {
                if (Board[y - troop[num].y][x] == 0 || Board[y][x - troop[num].x] == 0 || Is_enemy(Board[y][x], num)) {
                    return 1;
                }
            }
            if (((abs(y - troop[num].y) == 2) && (abs(x - troop[num].x) == 0)) || ((abs(x - troop[num].x) == 2) && abs(y - troop[num].y) == 0)) {
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if (abs(disx) + abs(disy) == 1) {
                return 1;
            } else if (((abs(tny - y) + abs(tny - y)) == 4) && ((abs(tny - y) == 2) && (abs(tnx - x) == 2))) {
                return 1;
            }
        }
    } else if ((num == 15) || (num == 35)) //  Priest
    {
        if (troop[num].filp == 0) {
            if (abs(disy) == abs(disx)) {
                ABSdis = abs(disy);

                for (i = 1; i <= ABSdis; i++) {
                    if (disx < 1) {
                        k = i * -1;
                    } else {
                        k = i;
                    }

                    if (Board[k + tny][k + tnx] != 0) {
                        if ((abs(k) == ABSdis) && (Is_enemy(num, Board[k + tny][k + tnx]))) {
                            return 1;
                        } else {
                            return 0;
                        }
                    }
                }
                return 1;
            }
        } else if (troop[num].filp == 1) {
            if ((abs(y - troop[num].y) == 1) && (abs(x - troop[num].x) == 1)) {
                if (((Board[troop[num].y][x] == 0) || (Board[y][troop[num].x] == 0))) {
                    return 1;
                }
            } else if (((abs(tny - y) + abs(tny - y)) == 4) && ((abs(tny - y) == 2) && (abs(tnx - x) == 2))) {
                return 1;
            }

            //else if ((((y-troop[num].y)==-2)&&(x-troop[num].x)==0)&&(Board[y-1][x]==0))   return 1;
        }
    } else if ((num == 16) || (num == 36)) //11,31 = Jester
    {
        if (troop[num].filp == 0) {
            if (((y - tny) == -1) && (abs(disx) == 1)) return 1;
            else if ((((y - troop[num].y) == 2) && (x - troop[num].x) == 0) && (Board[y - 1][x] == 0)) return 1;
            else if ((distance == 3) && ((disy) == 2 || abs(disx) == 2) && (Board[y][abs(x - tnx) / 2] == 0) && (y > 1)) return 1;
        } else if (troop[num].filp == 1) {
            if ((((y - tny) == -1) && (abs(disx) == 1)) || (((y - tny) == 1) && (abs(disx) == 0))) return 1;
            else if (abs(x - troop[num].x) > 2) return 0;
            else if (((y - troop[num].y > 0) && (abs(x - troop[num].x) > 0) && ((y - troop[num].y) == abs(x - troop[num].x)))) return 1;
        }
    } else if ((num == 17) || (num == 37)) //18, 38 wizard
    {
        if ((troop[num].filp == 0)) {
            if ((abs(y - troop[num].y) == 1) && (abs(x - troop[num].x) == 1)) {
                if (((Board[troop[num].y][x] == 0) || (Board[y][troop[num].x] == 0))) {
                    return 1;
                } else {
                    return 0;
                }
            } else if (distance == 1) {
                return 1;
            }
        } else if ((troop[num].filp == 1)) {
            if (((abs(tny - y) + abs(tnx - x)) == 4) && ((abs(tny - y) == 2) && (abs(tnx - x) == 2))) {
                return 1;
            } else if (((abs(y - troop[num].y) == 2) && (abs(x - troop[num].x) == 0)) || ((abs(x - troop[num].x) == 2) && abs(y - troop[num].y) == 0)) {
                return 1;
            }
        }
    }

    return 0;
}