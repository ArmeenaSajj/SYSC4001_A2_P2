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
#include <sys/sem.h>
#include <stdlib.h>

typedef struct { int multiple; int counter; } shared_t;
union semun{int val;struct semid_ds*buf;unsigned short*array;};
static void P(int id){struct sembuf op={0,-1,0};if(semop(id,&op,1)<0){perror("semop P");exit(1);}}
static void V(int id){struct sembuf op={0,+1,0};if(semop(id,&op,1)<0){perror("semop V");exit(1);}}

int main(void){
    key_t key_shm=0x5A6B7C01;
    key_t key_sem=0x5A6B7C02;

    int shmid=shmget(key_shm,sizeof(shared_t),0666);
    if(shmid<0){perror("shmget");return 1;}
    shared_t* sh=(shared_t*)shmat(shmid,NULL,0);
    if(sh==(void*)-1){perror("shmat");return 1;}

    int semid=semget(key_sem,1,0666);
    if(semid<0){perror("semget");return 1;}

    printf("[P2 %d] waiting for counter>100...\n",getpid());
    while(1){
        P(semid); int c=sh->counter; V(semid);
        if(c>100) break;
        usleep(50000);
    }

    while(1){
        P(semid); int c=sh->counter; int m=sh->multiple; V(semid);
        if(c%m==0) printf("[P2 %d] observed multiple: %d\n",getpid(),c);
        if(c>500){ printf("[P2 %d] counter=%d > 500, exiting.\n",getpid(),c); break; }
        usleep(90000);
    }

    shmdt(sh);
    return 0;
}
