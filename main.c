#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>
#include <dos.h>
#include <dir.h>
int Board[6][6]; // Y X
void setupboard(int t);//ไว้เริ่มเล่นset upเกม (T 1ไว้ debug ให้setup auto 0 ไว้แบบปกติ)
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
	int left;//เหลือกี่่ตัว
	int filp;
	struct pic pic[2][6];//filp line
} troop[41];//สร้างไว้คราวๆก่อน 1-20 p1 21-40 p2   1เเละ21 เป็นDuke 0เป็นช่องว่าง
int main(){
	int p,c = 0;// p = player c = command
	setup_troop_pic();
	printf("%d", Board[0][0]);
	while(c != 99){
	printf("1 : setup 2: view 3:move  5:summon /debug 7:viewnum 8:status 9:CanMove 10:summonNow 11:setupNow 99:end\n");
	scanf("%d", &c);
	if (c ==1 )
	{
		setupboard(0);
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
	else if (c == 10)
	{
		summon_now();
		viewboradnow();
	}
	else if (c == 11)
	{
		setupboard(1);
		viewboradnow();
	}
    }
    return 0;
}
void setupboard(int t){
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
	if (t== 0)
	{
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
	else{Board[5][3] = 1;leftout(1);leftout(21);Board[0][2] = 21;}
	
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
	int i, j, k,l ,num;
	for(i=0; i<=5; i++){
		for(j=0; j<=5; j++){
			printf("+");
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
				for (l = 0; l <= 5; l++){printf("++++ %d%d ++++",l,i);}
				printf("+\n");
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
void summon_now(){
	int re, x, y;
	printf("number\n");
	scanf("%d", &re);
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
		else{if (i == 2){if (j == 0){strcpy(troop[k].pic[j][i].move,"| | |i| | |\0");}
				else{strcpy(troop[k].pic[j][i].move,"| | |I| | |\0");}}
			//else if (((k <21)&&(i == 5))||((k >20)&&(i == 0))){strcpy(troop[i].pic[j][k].move,("|-----%02d--|",k));}
			else{ strcpy(troop[k].pic[j][i].move,"| | | | | |\0");}}
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

int CanMove(int num,int x,int y){ //1,21 = duke  
	int i,j,k, distance, ABSdis, disx, disy, tnx= troop[num].x,tny = troop[num].y; //2-4,22-24 = footman
	disx = x-troop[num].x;disy =y-troop[num].y;distance = abs(disy)+abs(disx);//5-7, 25-27 = PikeMan
	if (Is_ally(num, Board[y][x])) 	{return 0;}//8, 28 = Assassin 
	if (num >= 21) y = abs(5-y);
	if (num == 1|| num == 21)//Duke             9, 29 = Bowman
	{ if (troop[num].filp == 0)// %i%           10, 30 = champion
		{distance = x-troop[num].x ;            //11, 31 = Gragoon
			if (distance == 0 || y != troop[num].y){return 0;}//12,32 = General
			ABSdis = abs(distance);				//14, 34  == Knight
			for (i = 1; i <= ABSdis; i++){      //15, 35 == Marsall
				if (distance < 1)	{k = i*-1;}else{k = i;}
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
			if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))	{
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
		{
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
	}
	else if ((num==8)||(num==28))//8,28 = Assassin
	{
		if ((troop[num].filp == 0))
		{

			if ( (((disx)==0)&&(disy<=-2)) || ((abs(disx)>=2)&&((disy)>=2)&&(abs(disx)==abs(disy))))
			{return 1;/*
				if (((x-troop[num].x)>0)&&(Board[tny+1][tnx+1]==0)){return 1;}
				else if (((x-troop[num].x)==0)&&(Board[tny-1][tnx]==0)){return 1;}
				else if (((x-troop[num].x)<0)&&(Board[tny+1][tnx-1]==0)){return 1;	}*/
			}
		}
		else if ((troop[num].filp == 1))
		{
			if ( (((disx)==0)&&(disy>=2)) || ((abs(disx)>=2)&&((disy)<=-2)&&(abs(disx)==abs(disy))))
			{return 1; /*
				if (((x-troop[num].x)>0)&&(Board[tny-1][tnx-1]==0)){return 1;}
				else if (((x-troop[num].x)==0)&&(Board[tny+1][tnx]==0)){return 1;}
				else if (((x-troop[num].x)<0)&&(Board[tny-1][tnx+1]==0)){return 1;	}*/
			}
		}
	}
	else if ((num== 9)||(num==29 ))//  9,29 = Bowman
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
			if (((y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))	{
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
	else if ((num== 10)||(num==30 ))// 10,30 = champion
	{	distance = abs(y-troop[num].y)+abs(x-troop[num].x);
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
	else if ((num== 11)||(num==31 ))//11,31 = Gragoon 
	{
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
				if (disx < 1)	{k = i*-1;}else{k = i;}
				if (Board[k+tny][k+tnx] != 0)
				{
					if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+tny][k+tnx])))
					{return 1;	}
					else{ return 0;}
				}
			}
			return 1;
			}
			else if ((y-troop[num].y==-2)&&(abs(x-troop[num].x)==1)){return 1;	}
		}
	}
	else if ((num== 12)||(num==32 ))//12,32 = General
	{
		if ((troop[num].filp == 0))
		{
			if((distance == 1)&&(disx==0)){return 1;}
			else if (((distance == 2)&&(disy==0))&&(Board[abs(y-tny)/2][tnx]==0)){return 1;}
			else if ((abs(x-tnx)==1)&&((y-tny)==-2)){return 1;} 
		}
		else if ((troop[num].filp == 1))
		{	if ((abs(x-tnx)==1)&&((y-tny)==-2)){return 1;}
			else if (((distance == 2)&&(disy==0))&&(Board[abs(y-tny)/2][tnx]==0)){return 1;}
			else if ((distance == 1)&&(disy!=1)){return 1;}
			
		}
	}
	else if ((num== 13)||(num==34 ))//13, 34 = knight
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
			{	return 1;	}
			distance = y-troop[num].y ;// i
			//printf("%d\n", distance);// %
			if (distance >= 0 || x != troop[num].x){return 0;}
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
	else if ((num== 14)||(num== 34 ))// 14, 34 = Marshall
	{
		if ((troop[num].filp == 0))
		{if(disy==0){distance = x-troop[num].x ;            
			if (distance == 0 || y != troop[num].y){return 0;}
			ABSdis = abs(distance);				
			for (i = 1; i <= ABSdis; i++){
				if (distance < 1)	{k = i*-1;}else{k = i;}
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
			if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))	{
				if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
				{return 1;}
				else{ return 0;}
			}
		}
	}
	else if ((num== 15)||(num==35 ))// 15, 35 = Seer
	{
		if ((troop[num].filp == 0))
		{
			if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))	{
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
	else if ((num== 16)||(num==16 ))// 16, 36 = Priest
	{
		if ((troop[num].filp == 0))
		{if (abs(disy)==abs(disx))
			{ABSdis = abs(disy);
			for (i = 1; i <= ABSdis; i++){
				if (disx < 1)	{k = i*-1;}else{k = i;}
				if (Board[k+tny][k+tnx] != 0)
				{
					if ((abs(k) == ABSdis) &&( Is_enemy(num,Board[k+tny][k+tnx])))
					{return 1;	}
					else{ return 0;}
				}
			}
			return 1;
			}
		}
		else if ((troop[num].filp == 1))
		{if ((abs(y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))	{
				if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
				{return 1;}}
		else if (((abs(tny-y)+abs(tny-y))==4)&&((abs(tny-y)==2)&&(abs(tnx-x)==2))){return 1;}
		}
		}
	else if ((num== 17)||(num==37 ))// 17, 37 = LongBowman
	{
		if ((troop[num].filp == 0))
		{
			if (abs(disx)+abs(disy) == 1){return 1;}
		}
		else if ((troop[num].filp == 1))
		{if (((y-troop[num].y)==1)&&(abs(x-troop[num].x)==1))	{
				if (((Board[troop[num].y][x]==0)||(Board[y][troop[num].x]==0)))
				{return 1;	}
		}
	}
    }
	else if ((num== 18)||(num==38 ))//18, 38 wizard
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
void CanMove_map(int x, int y){
	int i, j;
	for (i = 0; i <= 5; i++){
		for (j = 0; j <= 5; j++){
			if (CanMove(Board[y][x], j, i) != 0)
			{
				printf("+ ");
			}
			else if((i==y)&&(j==x)){if (troop[Board[y][x]].filp == 0){printf("i ");}
			else if (troop[Board[y][x]].filp == 1){printf("I ");} 
		}
			else{printf("- ");}
		if (j == 5)	{printf(" %d \n", i);}
		}
	}
	printf("0 1 2 3 4 5 \n ");
}
