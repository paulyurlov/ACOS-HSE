#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

//задача была разобрана на семинаре

int mysys(const char* str) {
    int pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (pid) {
        int status; 
        waitpid(pid, &status, 0);
        if (WIFSIGNALED(status)) {
        return 128 + WTERMSIG(status);
        }
        return WEXITSTATUS(status);
    } else {
        execlp("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    }
}