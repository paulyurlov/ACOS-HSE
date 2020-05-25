#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


void copy_file(int in_fd, int out_fd) {
    char buffer[4096];
    ssize_t input;
    ssize_t output;
    input = read(in_fd, buffer, 4096);
    while (input > 0) {
        output = write(out_fd, buffer, input);
        while (output < input) {
            output += write(out_fd, buffer + output, input - output);
        }
        input = read(in_fd, buffer, 4096);
    }
}