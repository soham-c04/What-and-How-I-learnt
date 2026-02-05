//#include <graphics.h>
#include <stdio.h>
//#include <math.h>
//#include <windows.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <time.h>
//#include <unistd.h>
//#include <sys/time.h>


int main(){
//	if(GetAsyncKeyState('A')) printf("A"); //windows.h
//	int k;
//	if(_kbhit()) k=_getch();
//	else k=-1;
	time_t t0;
	time(&t0);
	printf("%s",ctime(&t0));
	return 0;
}
