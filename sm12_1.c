#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int file = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0600);
    unsigned short inlet;
    unsigned short head;
    unsigned short tail;
    while (scanf("%hu", &inlet) != EOF) {
        tail = inlet >> 8;
        head = (inlet & 255) << 8;
        inlet = tail | head;
        write(file, &inlet, 2);
    }
    close(file);
    return 0;
}
