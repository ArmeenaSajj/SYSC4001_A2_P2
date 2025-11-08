#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    long counter=0, cycle=0;
    printf("[P2] pid=%d, will stop when counter<-500\n",getpid());
    while(counter>=-500){
        if(counter%3==0) printf("Cycle %ld: %ld is a multiple of 3 [P2 %d]\n",cycle,counter,getpid());
        counter--; cycle++;
        usleep(200000);
    }
    printf("[P2 %d] reached %ld (< -500). Exiting.\n",getpid(),counter);
    return 0;
}
