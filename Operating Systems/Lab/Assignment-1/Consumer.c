#include<fcntl.h>    
#include<sys/mman.h>  
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>

int main(){
	const int size=4096;
    int shm_id=shm_open("22cs02002.txt",O_RDONLY, 0666);
    ftruncate(shm_id,size);
    void *ptr=mmap(0,size,PROT_READ,MAP_SHARED,shm_id,0);
    printf("Deleted character: ");
    printf("%c\n",(char)ptr);
    shm_unlink("22cs02002.txt");
    return 0;
}