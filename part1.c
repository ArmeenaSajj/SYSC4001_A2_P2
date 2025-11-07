/**
 * @author Armeena Sajjad, 101295773
 * @author Ajay Uppal, 101308579
 * 
 */
#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
static void sleep_ms(int ms){ usleep((useconds_t)ms*1000); }
int main(void) {
    pid_t pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }
    if (pid == 0) {
        unsigned long c = 0;
        while (1) {
            printf("[Child %d] counter=%lu\n", getpid(), c++);
            fflush(stdout);
            sleep_ms(300);
        }
    } else {
        unsigned long c = 0;
        while (1) {
            printf("[Parent %d] counter=%lu\n", getpid(), c++);
            fflush(stdout);
            sleep_ms(300);
        }
    }
}
