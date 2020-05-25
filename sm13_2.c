#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    struct stat fil;
    unsigned long long quantity = 0;
    for (int i = 1; i < argc; ++i) {
        int file = lstat(argv[i], &fil);
        if (file >= 0) {
            if (S_ISREG(fil.st_mode) && (!S_ISLNK(fil.st_mode)) && (fil.st_nlink == 1)) {
                quantity += fil.st_size;
            }
        }
    }
    printf("%llu\n", quantity);
    return 0;
}
