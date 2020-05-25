#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int mysystem(const char* cmd) {
    char* sup = (char*) malloc(sizeof(char) * strlen(cmd));
    strcpy(sup, cmd);
    char* arg = strtok(sup, " \t\n\v\f\r");
    char** vec_of_args = (char**) malloc(sizeof(char*) * 100);
    unsigned long long i = 0;
    unsigned long long size = 100;
    while(arg != NULL) {
        if (i > size) {
            vec_of_args = (char**)realloc(vec_of_args, sizeof(char*) * 2 * (size + 1));
            size = size * 2;
        }
        vec_of_args[i] = (char*) malloc((strlen(arg) + 1) * sizeof(char));
        strcpy(vec_of_args[i], arg);
        arg = strtok(NULL, " \t\n\v\f\r");
        ++i;
    }
    if (i == 0) {
        return -1;
    }
    int pid;
    pid = fork();
    if (!pid) {
        execvp(vec_of_args[0], vec_of_args);
        _exit(1);
    } else if (pid <= -1) {
        return -1;
    }
    int st;
    waitpid(pid, &st, 0);
    if (WIFSIGNALED(st))
        return WTERMSIG(st) + 1024;
    return WEXITSTATUS(st);
}

//for (unsigned long long j = 0; j < i; ++j) {
//        free(vec_of_args[j]);
//    }
//    free(vec_of_args);