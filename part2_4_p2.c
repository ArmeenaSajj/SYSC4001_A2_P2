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
    int shmid=shmget(key,sizeof(shared_t),0666);
    if(shmid<0){perror("shmget");return 1;}
    shared_t* sh=(shared_t*)shmat(shmid,NULL,0);
    if(sh==(void*)-1){perror("shmat");return 1;}

    printf("[P2 %d] started. Waiting for counter>100...\n",getpid());
    while(sh->counter<=100) usleep(50000);

    printf("[P2 %d] detected counter=%d.\n",getpid(),sh->counter);
    while(1){
        int c=sh->counter;
        if(c%sh->multiple==0) printf("[P2 %d] observed multiple: %d\n",getpid(),c);
        if(c>500){ printf("[P2 %d] counter=%d > 500, exiting.\n",getpid(),c); break; }
        usleep(90000);
    }

    shmdt(sh);
    return 0;
}
