#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <dos.h>
#include <dir.h>
int Board[6][6]; // Y X
void setupboard();//ไว้เริ่มเล่นset upเกม
void viewboradnow();//ปริ้นกระดาษให้ดู
void movetroop(int x1, int y1, int x2, int y2);//เดิน กะ กิน เสด1ตัว
void summon(int player);//สุ่มเรียกตัวละคร ยังไม่เสด
void setup_troop_pic();//ตั้งเเค่ตัวละคร
void viewboradnum();//ดูรหัสตัวละครบนกระดาน
void filp_troop(int i);//กลับด้านตัวละคร
void SetColor(int ForgC);//ตั้งค่าสีตัวอักษร
void CanMove_map(int x, int y);//ฟังก์ชั่นเช็คว่าตัวนั้นเดินไปได้ไหม (ข้อมูลการเดินทั้งหมดอยู่ตรงนั้น)

struct pic{
	char move[17];
};
struct Troop{
	int x;
	int y;
	int left;
	int filp;//เหลือกี่่ตัว
	struct pic pic[2][6];//filp line
} troop[41];//สร้างไว้คราวๆก่อน 1-20 p1 21-40 p2   1เเละ21 เป็นDuke 0เป็นช่องว่าง
int main(){
	int p,c = 0;// p = player c = command
	setup_troop_pic();
	printf("%d", Board[0][0]);
	while(c != 99){
	printf("1 : setupboard 2: viewboradnow 3:move  5:summon 7:viewboradnum 99:end\n");
	scanf("%d", &c);
	if (c ==1 )
	{
		setupboard();
		viewboradnow();
	}
	else if ( c == 2)
	{
		viewboradnow();
	}
	else if (c ==3)
	{
		int x1, y1, x2, y2;
		printf("x1 y1 x2 y2\n");
		scanf("%d %d %d %d",&x1, &y1, &x2, &y2);
		if (CanMove(Board[y1][x1],x2,y2))
		{
			movetroop(x1,y1,x2,y2);
			viewboradnow();
		}
		else{printf("Nooooo!!\n");}
		
	}
	else if(c == 5){
		summon(1);
		viewboradnow();
	}
	else if (c == 7)
	{
		viewboradnum();
	}
	else if (c == 8)
	{
		Sstatus();
	}
	else if (c == 9)
	{
		int x1, y1;
		printf("x y\n");
		scanf("%d %d",&x1, &y1);
		CanMove_map( x1, y1);
	}
    }
    return 0;
}
void setupboard(){
	srand(time(NULL));
	int i, j, ans = 0;
	for(i=0; i<=5; i++){
		for(j=0; j<=5; j++){
				Board[i][j] = 0;
		}
	}

	for(i = 1; i <= 41; i++)	{
		troop[i].left = 1;
		troop[i].filp = 0;
	}
	Board[0][1] = 0;//Bug
	viewboradnow();
	while((ans != 3)&& (ans != 2)){
	printf("Player1  plan Duke on Y ( 2 or 3 )\n");
	scanf("%d", &ans);
	}
	Board[5][ans] = 1;leftout(1);
	if (ans == 3)
	{
		Board[0][2] = 21;
	}
	else{
		Board[0][3] = 21;
	}
	leftout(21);

}

void viewboradnum(){
	int i, j;
	for(i=0; i<=5; i++){
		for(j=0; j<=5; j++){
		printf("%02d |", Board[i][j]);
		if (j == 5){
			printf(" %d\n",i);
			printf("___|___|___|___|___|___|\n");
		}
		}
	}
	printf(" 0   1   2   3   4   5  \n");;
}

void viewboradnow(){
	int i, j, k, num;
	for(i=0; i<=5; i++){
		for(j=0; j<=5; j++){
			for (k = 0; k <= 5; k++)
			{
				num = Board[i][k];
				if (num >=21)
				{
					SetColor(9);troop[num].x =k;troop[num].y =i;
				}
				else if (num <21 && num != 0)
				{
					SetColor(12);;troop[num].x =k;troop[num].y =i;
				}
				else{SetColor(15);}
				//printf("%di%dj%dk ",i,j,k);
				printf("%.11s",troop[num].pic[troop[num].filp][j].move);
				SetColor(15);
				printf("+");
			}
		printf("\n");
		if (j == 5){
				printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
			}
		}
		
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
	else{troop[k].filp = 1;}
}
void summon(int player){
	int re = rand()%(20*player), x,y;
	printf("%d\n", re);
	printf("X Y\n");
	scanf("%d %d,",&x,&y);
	Board[y][x] = re;
	leftout(re);
	troop[re].x = x;
	troop[re].y = y;
}
void setup_troop_pic(){//@ :move O :jump  %:slide ^:jump slide C:command *:strike 
	int i, k, j;

	for (k = 0 ; k <=41 ; k++){
		for (j = 0; j < 2; j++){
		for (i = 0; i < 6; i++){
		if (k == 0){strcpy(troop[k].pic[j][i].move,"           ");}
		else{strcpy(troop[k].pic[j][i].move,"| | | | | |\0");}
		//printf("%s+\n",troop[k].pic[i].move);
	}}}
	//duke 1 21
	for (i = 1; i <= 21; i+=20)
	{
		if (i == 1)	{k =0;}else{k =5;}
		strcpy(troop[i].pic[0][2].move,"| |%|I|%| |");
		strcpy(troop[i].pic[0][abs(k-5)].move,"|--Duke---|");

		strcpy(troop[i].pic[1][abs(k-1)].move,"| | |%| | |");
		strcpy(troop[i].pic[1][abs(k-2)].move,"| | |i| | |");
		strcpy(troop[i].pic[1][abs(k-3)].move,"| | |%| | |");
		strcpy(troop[i].pic[1][abs(k-5)].move,"|---Duke--|");
	}
}
void leftout(int i){
	if (troop[i].left != 0)
	{
		troop[i].left -= 1;
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
	else{return 0;}
}
int Is_enemy(int numA, int numB){
	if ((numA >=21)&&((numB <21)&& (numB != 0)))
	{
		return 1;
	}
	else if((numB >=21)&&((numA <21)&& (numA != 0))){
		return 1;
	}
	else{return 0;}
}
void Sstatus(){
	int i,k,j;
	for (i = 0; i < 42; i++)
	{
		printf("%d have %d X%d Y%d     F%d \n ", i, troop[i].left, troop[i].x, troop[i].y, troop[i].filp);
	}
}
void SetColor(int ForgC)
 {
 WORD wColor;
  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

int CanMove(int num,int x,int y){
	int i,j,k, distance, ABSdis;
	if (num == 1|| num == 21){
		if (troop[num].filp == 0)// %i%
		{
			distance = x-troop[num].x ;
			if (distance == 0 || y != troop[num].y){return 0;}
			ABSdis = abs(distance);
			for (i = 1; i <= ABSdis; i++){
				if (distance < 1)	{k = i*-1;}else{k = i;}
				if (Board[y][k+troop[num].x] != 0)
				{
					if ((k == ABSdis) &&( Is_enemy(num,Board[y][k+troop[num].x])))
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
				if (distance < 1)	{k = i*-1;}else{k = i;}
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
			distance = abs(y-troop[num].y)+abs(x-troop[num].x)
			if (distance == 1){
				if ((Board[y][x]==0)||(Is_enemy(num,Board[y][x]))){
					return 1;
				}
				else{return 0;}
			}
			else{return 0;}
		}
		else if (if (troop[num].filp == 1))	{
			/* code */
		}
	}
}
void CanMove_map(int x, int y){
	int i, j;
	for (i = 0; i <= 5; i++){
		for (j = 0; j <= 5; j++){
			if (CanMove(Board[y][x], j, i) != 0)
			{
				printf("+ ");
			}
			else{printf("- ");}
		if (j == 5)	{printf("\n" );}
		}
	}
}
