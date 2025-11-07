/**
 * @author Armeena Sajjad, 101295773
 * @author Ajay Uppal, 101308579
 * 
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main() {
    pid_t pid = fork();
    int cycle = 0;
    key_t key = ftok(".", 'S');
    key_t key_sem = ftok(".", 'M');
    int status;

    int shmid = shmget(key, sizeof(int) * 2, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); exit(1); }
    int *shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (int *)-1) { perror("shmat"); exit(1); }

    int semid = semget(key_sem, 1, 0666 | IPC_CREAT);
    if (semid == -1) { perror("semget"); exit(1); }

    int *multiple = &shm_ptr[0];
    int *shared_vars = &shm_ptr[1];
    *multiple = 3;
    *shared_vars = 0;

    if (semctl(semid, 0, SETVAL, 1) == -1) { perror("semctl SETVAL"); exit(1); }

    struct sembuf lock  = (struct sembuf){0, -1, 0};
    struct sembuf unlock = (struct sembuf){0,  1, 0};

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        char *args[] = {"./process2", NULL};
        execvp("./process2", args);
        perror("execvp");
        exit(1);
    } else {
        while (*shared_vars <= 500) {
            if (semop(semid, &lock, 1) == -1) { perror("semop lock"); exit(1); }

            if (*shared_vars > 100) {
                if (*shared_vars % *multiple == 0)
                    printf("Process 1: Cycle %d - %d is a multiple of %d\n", cycle, *shared_vars, *multiple);
                else
                    printf("Process 1: Cycle %d - Counter %d\n", cycle, *shared_vars);
            }

            (*shared_vars)++;
            cycle++;

            if (semop(semid, &unlock, 1) == -1) { perror("semop unlock"); exit(1); }

            usleep(50000);
        }

        waitpid(pid, &status, 0);

        if (shmdt(shm_ptr) == -1) perror("shmdt");
        if (shmctl(shmid, IPC_RMID, 0) == -1) perror("shmctl IPC_RMID");
        if (semctl(semid, 0, IPC_RMID) == -1) perror("semctl IPC_RMID");
    }
    return 0;
}
