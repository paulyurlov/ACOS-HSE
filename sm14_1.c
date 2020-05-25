#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    long long result = 0;
    DIR* inlet_dir = opendir(argv[1]);
    if (inlet_dir == NULL) {
        printf("0\n");
    } else {
        struct dirent* file;
        uid_t user =getuid();
        struct stat fil;
        while ((file = readdir(inlet_dir)) != NULL) {
            char fullpath[PATH_MAX + 256];
            snprintf(fullpath, PATH_MAX, "%s/%s", argv[1], file->d_name);
            if (stat(fullpath, &fil) == 0) {
                if (S_ISREG(fil.st_mode) && (fil.st_uid == user) && isupper((file->d_name)[0])) {
                    result += fil.st_size;
                }
            }
        }
        printf("%lld\n", result);
    }
    closedir(inlet_dir);
    return 0;
}
