#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void){
    pid_t pid=fork();
    if(pid<0){perror("fork");return 1;}
    if(pid==0){
        execl("./part2_3_p2","part2_3_p2",(char*)NULL);
        perror("execl");
        _exit(127);
    }else{
        printf("[P1 %d] waiting for child %d...\n",getpid(),pid);
        int status=0;
        waitpid(pid,&status,0);
        printf("[P1 %d] child finished (status=%d). Exiting P1.\n",getpid(),status);
    }
}
