#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>


int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Wrong input");
        exit(1);
    }
    int fd1[2], fd2[2];
    int pid1, pid2;
    if (pipe(fd1) < 0) {
        perror("pipe");
        exit(1);
    }
    if (pipe(fd2) < 0) {
        perror("pipe");
        exit(1);
    }
    unsigned long long n = strtoull(argv[1], NULL, 10);
    FILE* put_to_first = fdopen(fd1[1], "w");
    FILE* take_for_first = fdopen(fd1[0], "r");
    FILE* put_to_second = fdopen(fd2[1], "w");
    FILE* take_for_second = fdopen(fd2[0], "r");
    if ((pid1 = fork()) < 0) {
        exit(1);
    }
    if (pid1 == 0) {
        fclose(take_for_second);
        fclose(put_to_first);
        unsigned long long x;
        while (fscanf(take_for_first, "%llu", &x) == 1) {
            if (x == n) {
                break;
            }
            printf("1 %llu\n", x);
            fflush(stdout);
            fprintf(put_to_second, "%llu\n", ++x);
            fflush(put_to_second);
        }
        fclose(take_for_first);
        fclose(put_to_second);
        exit(0);
    }
    if ((pid2 = fork()) < 0) {
        exit(1);
    }
    if (pid2 == 0) {
        fclose(put_to_second);
        fclose(take_for_first);
        fprintf(put_to_first, "1\n");
        fflush(put_to_first);
        unsigned long long x;
        while (fscanf(take_for_second, "%llu", &x) == 1) {
            if (x == n) {
                break;
            }
            printf("2 %llu\n", x);
            fflush(stdout);
            fprintf(put_to_first, "%llu\n", ++x);
            fflush(put_to_first);
        }
        fclose(take_for_second);
        fclose(put_to_first);
        exit(0);
    }
    fclose(take_for_second);
    fclose(put_to_first);
    fclose(take_for_first);
    fclose(put_to_second);
    wait(NULL);
    wait(NULL);
    printf("Done\n");
    fflush(stdout);
    return 0;
}