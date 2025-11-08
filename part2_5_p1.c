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

    int shmid=shmget(key_shm,sizeof(shared_t),IPC_CREAT|0666);
    if(shmid<0){perror("shmget");return 1;}
    shared_t* sh=(shared_t*)shmat(shmid,NULL,0);
    if(sh==(void*)-1){perror("shmat");return 1;}

    int semid=semget(key_sem,1,IPC_CREAT|0666);
    if(semid<0){perror("semget");return 1;}
    union semun su; su.val=1; if(semctl(semid,0,SETVAL,su)<0){perror("semctl");return 1;}

    P(semid); sh->multiple=3; sh->counter=0; V(semid);

    pid_t pid=fork();
    if(pid<0){perror("fork");return 1;}
    if(pid==0){
        execl("./part2_5_p2","part2_5_p2",(char*)NULL);
        perror("execl"); _exit(127);
    }

    printf("[P1 %d] child=%d; multiple=%d\n",getpid(),pid,3);
    while(1){
        P(semid); int c=++(sh->counter); int m=sh->multiple; V(semid);
        if(c%m==0) printf("[P1 %d] counter=%d is multiple of %d\n",getpid(),c,m);
        if(c>500){ printf("[P1 %d] counter=%d > 500, exiting.\n",getpid(),c); break; }
        usleep(80000);
    }

    shmdt(sh);
    shmctl(shmid,IPC_RMID,NULL);
    semctl(semid,0,IPC_RMID);
    return 0;
}
