#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

void resetscreen(){
	HANDLE hout;
	COORD position;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X=0;
	position.Y=0;
	SetConsoleCursorPosition(hout,position);
}
int main(){
	int i,tme=0;
	time_t t0,t1;
	time( &t0 );
	for(i=0;;i++){
		time(&t1);
		if(t0!=t1){
			t0=t1;
			printf("Time: %ds",tme);
			tme++;
			resetscreen();
		}
	}
	return 0;
}
