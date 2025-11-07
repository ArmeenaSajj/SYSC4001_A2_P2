/**
 * @author Armeena Sajjad, 101295773
 * @author Ajay Uppal, 101308579
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
int main() {
    key_t key = ftok(".", 'S');
    key_t key_sem = ftok(".", 'M');

    int shmid = shmget(key, sizeof(int) * 2, 0666);
    if (shmid == -1) { perror("shmget"); exit(1); }
    int *shm_ptr = (int *)shmat(shmid, NULL, 0);
    if (shm_ptr == (int *)-1) { perror("shmat"); exit(1); }

    int semid = semget(key_sem, 1, 0666);
    if (semid == -1) { perror("semget"); exit(1); }

    int *multiple = &shm_ptr[0];
    int *shared_vars = &shm_ptr[1];

    struct sembuf lock  = (struct sembuf){0, -1, 0};
    struct sembuf unlock = (struct sembuf){0,  1, 0};

    long counter = 0;
    unsigned long cycle = 0;

    while (1) {
        if (semop(semid, &lock, 1) == -1) { perror("semop lock"); exit(1); }
        int gate = *shared_vars;
        if (semop(semid, &unlock, 1) == -1) { perror("semop unlock"); exit(1); }
        if (gate > 100) break;
        usleep(50000);
    }

    while (1) {
        if (semop(semid, &lock, 1) == -1) { perror("semop lock"); exit(1); }

        int m = *multiple;
        int c = *shared_vars;
        int stop = (c > 500);

        if (!stop) {
            if (counter % m == 0)
                printf("Process 2: Cycle %lu - %ld is a multiple of %d ; shared=%d\n", cycle, counter, m, c);
            else
                printf("Process 2: Cycle %lu ; shared=%d\n", cycle, c);
        }

        if (semop(semid, &unlock, 1) == -1) { perror("semop unlock"); exit(1); }

        if (stop) break;

        counter--;
        cycle++;
        if (counter < -500) break;

        usleep(60000);
    }

    if (shmdt(shm_ptr) == -1) perror("shmdt");
    return 0;
}