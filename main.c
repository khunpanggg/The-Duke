#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int Board[5][5]; // Y X
int player = 1; //มีเเค่  กะ 
void setupboard(); //ไว้เริ่มเล่น1 กะ 2
void viewboradnow(); //ปริ้นกระดาษให้ดู
void movetroop(int x1, int y1, int x2, int y2); //เดิน กะ กิน
void summon(int player); //สุ่มเรียกตัวละคร
struct Troop{
	int x;
	int y;
	int left;//เหลือกี่่ตัว
} troop[41];//สร้างไว้คราวๆก่อน 1-20 p1 21-40 p2   1เเละ21 เป็นDuke 0เป็นช่องว่าง

int main(){
	int c = 0;
	player = 1;
	while(c != 4){
	printf("1 : setupboard 2: viewboradnow 3:move 4 : end 5:summon\n");
	scanf("%d", &c);
	if (c ==1 )
	{
		setupboard();
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
		movetroop(x1,y1,x2,y2);
	}
	else if(c == 5){
		summon(1);
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
	}
	troop[0].left = 0;
	viewboradnow();
	while((ans != 3)&& (ans != 2)){
	printf("Player1  plan Duke on Y ( 2 or 3 )\n");
	scanf("%d", &ans);
	}
	Board[5][ans] = 1;
	troop[1].x = ans;
	troop[1].y = 5;
	troop[1].left -= 1;
	if (ans == 3)
	{
		Board[0][2] = 21;
		troop[21].x = 2;
	}
	else{
		Board[0][3] = 21;
		troop[21].x = 3;
	}
	troop[21].y = 0;
	troop[21].left -= 1;

}
void viewboradnow(){
	int i, j;
	for(i=0; i<=5; i++){
		for(j=0; j<=5; j++){
		printf("%02d |", Board[i][j]);
		if (Board[i][j] != 0)
		{
			troop[Board[i][j]].x = j;
			troop[Board[i][j]].y = i; 
		}
		if (j == 5){
			printf(" %d\n",i);
			printf("___|___|___|___|___|___|\n");
		}
		}
	}
	printf(" 0   1   2   3   4   5  \n");;
}
void movetroop(int x1, int y1, int x2, int y2){
	Board[y2][x2] = Board[y1][x1];
	Board[y1][x1] = 0;
}
void summon(int player){
	int re = rand()%(20*player), x,y;
	while (troop[re].left == 0)
	{
		re = rand()%(20*player);
	}
	printf("%d\n", re);
	printf("X Y\n");
	scanf("%d %d,",&x,&y);
	while (ifsummon(x,y) != 1)
	{
		printf("X Y\n");
	    scanf("%d %d,",&x,&y);
	}
	Board[y][x] = re;
	troop[re].x = x;
	troop[re].y = y;
	troop[re].left -= 1;
}
int ifsummon(x,y){
	int duke;
	if (player == 1){
		duke = 1;
	}
	else{
		duke = 21;
	}
	if ( ((x<=5)&&(x>=0)) && ((y<=5)&&(y>=0)) ){
		if ((x == troop[duke].x)&&((y == (troop[duke].y)-1)|| (y == (troop[duke].y)+1)))
		{
			printf("1111\n");
			return 1;
		}
		else if ((y == troop[duke].y)&&  ((x == (troop[duke].x)-1)|| (x == (troop[duke].x)+1)) )
		{
			printf("1111\n");
			return 1;
		}
		else{
			printf("x%d y%d dx%d dy%d \n",x,y, troop[duke].x, troop[duke].y);
			printf("00000\n");
			return 0;
		}
	}
	printf("3\n");
	return 3;
}
