/**
 *
 * @author Armeena Sajjad
 * @author Ajay Uppal
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

typedef struct { int multiple; int counter; } shared_t;

int main(void){
    key_t key=0x4A3C2B01;
    int shmid=shmget(key,sizeof(shared_t),IPC_CREAT|0666);
    if(shmid<0){perror("shmget");return 1;}
    shared_t* sh=(shared_t*)shmat(shmid,NULL,0);
    if(sh==(void*)-1){perror("shmat");return 1;}

    sh->multiple=3;
    sh->counter=0;

    pid_t pid=fork();
    if(pid<0){perror("fork");return 1;}
    if(pid==0){
        execl("./part2_4_p2","part2_4_p2",(char*)NULL);
        perror("execl");
        _exit(127);
    }

    printf("[P1 %d] child=%d; multiple=%d\n",getpid(),pid,sh->multiple);
    while(1){
        int c=++(sh->counter);
        if(c%sh->multiple==0) printf("[P1 %d] counter=%d is multiple of %d\n",getpid(),c,sh->multiple);
        if(c>500){ printf("[P1 %d] counter=%d > 500, exiting.\n",getpid(),c); break; }
        usleep(80000);
    }

    shmdt(sh);
    shmctl(shmid,IPC_RMID,NULL);
    return 0;
}
