#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>

//было на семинаре

int main(int argc, char ** argv) {
    if (argc != 5) {
        printf("Wrong input");
        exit(1);
    }
    int fd[2];
    int pid1;
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    if ((pid1 = fork()) < 0) {
        exit(1);
    }
    if (pid1 == 0) {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        for (int i = 0; i < 2; ++i) {
            if ((pid1 = fork()) < 0) {
                _exit(1);
            }
            if (pid1 == 0) {
                execlp(argv[i + 1], argv[i + 1], NULL);
                _exit(1);
            }
            wait(NULL);
        }
        exit(0);
    }
    close(fd[1]);
    if ((pid1 = fork()) < 0) {
        exit(1);
    }
    if (pid1 == 0) {
        dup2(fd[0], 0);
        int out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
        dup2(out_fd, 1);
        close(fd[0]);
        close(out_fd);
        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    close(fd[0]);
    wait(NULL);
    wait(NULL);
    return 0;
}