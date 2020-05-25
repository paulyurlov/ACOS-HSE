#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>


int main (int argc, char** argv) {
    if (argc != 2 ) {
        printf("Wrong input");
        exit(1);
    }
    char* script = "lolkek.c";
    int fd = open(script, O_WRONLY | O_CREAT | O_TRUNC, 0700);
    dprintf(fd, "#include <stdio.h>\n\n");
    dprintf(fd, "int main() {\n");
    dprintf(fd, "    int x;\n");
    int x;
    while (scanf("%d", &x) == 1) {
        dprintf(fd, "    x = %d;\n", x);
        dprintf(fd, "    printf(\"%%s\n\", %s);\n", argv[2]);
    }
    dprintf(fd, "    return 0;\n");
    close(fd);
    if (!fork()) {
        execlp("gcc", "gcc", "lolkek.c", "-o", "lolkek.out", NULL);
        _exit(0);
    }
    wait(NULL);
    execlp("./lolkek.out", "./lolkek.out", NULL);
    return 0;
}