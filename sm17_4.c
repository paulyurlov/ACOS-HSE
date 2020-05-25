#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <fcntl.h>

//было на семенаре

int main(int argc, char** argv) {
    if (argc < 2 ) {
        printf("Wrong input");
        exit(1);
    }
    char* script = "/tmp/apb.py";
    int fd = open(script, O_WRONLY | O_CREAT, 0700);
    dprintf(fd, "#!/usr/bin/python3\n");
    dprintf(fd, "print(%s", argv[1]);
    for (int i = 2; i < argc; ++i) {
        dprintf(fd, " * %s", argv[i]);
    }
    dprintf(fd, ")\n");
    dprintf(fd, "import os\nimport sys\nos.remove('%s')\n", script);
    close(fd);
    execlp(script, script, NULL);
    return 0;
}