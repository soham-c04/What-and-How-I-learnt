#include<fcntl.h>    
#include<sys/mman.h>  
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
    srand(time(NULL));
	const int size=4096;
    int shm_id=shm_open("22cs02002.txt",O_CREAT | O_RDWR, 0666);
    ftruncate(shm_id,size);
    void *ptr=mmap(0,size,PROT_WRITE,MAP_SHARED,shm_id,0);
    char c=48+rand()%(256-48);
    printf("Inserted element: %c\n",c);
    sprintf(ptr,"%c",c);
    return 0;
}