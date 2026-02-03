#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#define f(n) for(i=0;i<n;i++)
#define r 20
#define c 40
#define ms 1000
#define top_left_corner printf("%c",201)
#define horizontal printf("%c",205)
#define top_right_corner printf("%c",187)
#define vertical printf("%c",186)
#define bottom_left_corner printf("%c",200)
#define bottom_right_corner printf("%c",188)
#define vertical_right printf("%c",204);
#define vertical_left printf("%c",185);
#define newline printf("\n")
#define HEAD printf("%c",178)
#define TAIL printf("%c",176)
#define FROG printf("%c",15)

int i,j,x,y;
int field[r][c],length=5,game=1,var,dir='d',score=0,tme=0,speed=200;
void print(){
	top_left_corner;
	f(c) horizontal;
	top_right_corner;
	newline;
	vertical;
	printf("Time:%3ds",tme);
	f(c-17) printf(" "); 
	printf("Score: %d",score);
	vertical;
	newline;
	//top_left_corner;
	vertical_right;
	f(c) horizontal;
	vertical_left
	//top_right_corner;
	newline;
	f(r){
		vertical;
		for(j=0;j<c;j++){
			switch(field[i][j]){
				case 0:
					printf(" ");
					break;
				case 1:
					TAIL;
					break;
				case 2:
					HEAD;
					break;
				case 3:
					FROG;
					break;
				default:
					printf("%c",field[i][j]);
			}
		}
		vertical;
		newline;
	}
	bottom_left_corner;
	f(c) horizontal;
	bottom_right_corner;
}
void snakeInitialize(){
	for(i=c/2-length;i<c/2;i++){
		field[r/2][i]=1;
	}
	field[r/2][c/2]=2;
	x=c/2;
	y=r/2;
}
void frog(){
	srand(time(0));
	int a=rand()%r;
	int b=rand()%c;
	while(field[a][b]!=0){
		a=rand()%r;
		b=rand()%c;
	}
	field[a][b]=3;
}
int input(){
	if(_kbhit()) return _getch();
	else return -1;
}
void movement(){
	var=input();
	var = tolower(var);
	if(var!=-1 && abs(dir-var)>5) dir=var;
	switch(dir){
		case 'w':
			y--;
			if(y!=-1) if(field[y][x]!=1) field[y+1][x]=1;
//			y=(y-1)%r; When it can pass through boundaries
//			y=(y+c)%r;
			break;
		case 'a':
			x--;
			if(x!=-1) if(field[y][x]!=1) field[y][x+1]=1;
//			x=(x-1)%c;
//			x=(x+c)%c;
			break;
		case 's':
			y++;
			if(y!=r) if(field[y][x]!=1) field[y-1][x]=1;
//			y=(y+1)%r;
			break;
		case 'd':
			x++;
			if(x!=c) if(field[y][x]!=1) field[y][x-1]=1;
//			x=(x+1)%c;
			break;
		case -1:
			break;
	}
	if(x==-1 || y==-1 || x==c || y==r) gameover();
	else if(field[y][x]==1) gameover();
	else{
		if(field[y][x]==3){
			frog();
			score++;
		}
		else tailremove();
		field[y][x]=2;
	}
}
void tailremove(){
	
}
void gameover(){
	game=0;
	field[r/2][c/2-5]=219;
	field[r/2][c/2-4]='G';
	field[r/2][c/2-3]='A';
	field[r/2][c/2-2]='M';
	field[r/2][c/2-1]='E';
	field[r/2][c/2-0]='-';
	field[r/2][c/2-0+1]='O';
	field[r/2][c/2+1+1]='V';
	field[r/2][c/2+2+1]='E';
	field[r/2][c/2+3+1]='R';
	field[r/2][c/2+4+1]=219;
	f(9){
		field[r/2-1][c/2-4+i]=220;
		field[r/2+1][c/2-4+i]=223;
	}
}
void resetscreen(){
	HANDLE hout;
	COORD position;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X=0;
	position.Y=0;
	SetConsoleCursorPosition(hout,position);
}
int main(){
	snakeInitialize();
	frog();
	int ii;
	time_t t0,t1;
	time( &t0 );
	for(ii=0;game;ii++){
		time(&t1);
		if(t0!=t1){
			t0=t1;
			tme++;
		}
		print();
		movement();
		resetscreen();
		if(!game) print();
		usleep(speed*ms);
	}
	return 0;
}
