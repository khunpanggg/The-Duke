#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int Board[5][5]; // Y X
void setupboard();
void viewboradnow();
void movetroop(int x1, int y1, int x2, int y2);
void summon(int player);
struct Troop{
	int x;
	int y;
	int left;
} troop[41];
int main(){
	int p,c = 0;
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
	viewboradnow();
	while((ans != 3)&& (ans != 2)){
	printf("Player1  plan Duke on Y ( 2 or 3 )\n");
	scanf("%d", &ans);
	}
	Board[5][ans] = 1;
	if (ans == 3)
	{
		Board[0][2] = 21;
	}
	else{
		Board[0][3] = 21;
	}

}
void viewboradnow(){
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
void movetroop(int x1, int y1, int x2, int y2){
	Board[y2][x2] = Board[y1][x1];
	Board[y1][x1] = 0;
}
void summon(int player){
	int re = rand()%(20*player), x,y;
	printf("%d\n", re);
	printf("X Y\n");
	scanf("%d %d,",&x,&y);
	Board[y][x] = re;
	troop[re].x = x;
	troop[re].y = y;
}
