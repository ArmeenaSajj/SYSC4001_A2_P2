#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    pid_t pid=fork();
    if(pid<0){perror("fork");return 1;}
    if(pid==0){
        execl("./part2_2_p2","part2_2_p2",(char*)NULL);
        perror("execl");
        _exit(127);
    }else{
        long counter=0, cycle=0;
        printf("[P1] pid=%d, child=%d\n",getpid(),pid);
        while(1){
            int is_mult=(counter%3==0);
            if(is_mult) printf("Cycle %ld: %ld is a multiple of 3 [P1 %d]\n",cycle,counter,getpid());
            else printf("Cycle %ld\n",cycle);
            counter++; cycle++;
            sleep(1);
        }
    }
}
