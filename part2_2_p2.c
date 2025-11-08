#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    long counter=0, cycle=0;
    printf("[P2] pid=%d, ppid=%d\n",getpid(),getppid());
    while(1){
        int is_mult=(counter%3==0);
        if(is_mult) printf("Cycle %ld: %ld is a multiple of 3 [P2 %d]\n",cycle,counter,getpid());
        else printf("Cycle %ld\n",cycle);
        counter--; cycle++;
        sleep(1);
    }
}
