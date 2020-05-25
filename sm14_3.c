#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>


int funccmp(const void* first, const void* second) {
    return strcasecmp(*(char* const*) first, *(char* const*) second);
}


void dopath(char* inlet_dir, char* output) {
    struct dirent *dirp;
    DIR *dp;
    if (strlen(inlet_dir) > PATH_MAX - 1) {
        return;
    }
    if ((dp = opendir(inlet_dir)) == NULL) {
        return;
    }
    if (output != NULL) {
        printf("cd %s\n", output);
    }
    char ** dirs_in_dir;
    unsigned long long i = 0;
    unsigned long long size = 1000;
    dirs_in_dir = malloc(size * sizeof(char*));
    while ((dirp = readdir(dp)) != NULL) {
        if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
            continue;
        if(dirp->d_type == DT_DIR && strlen(dirp->d_name) < PATH_MAX) {
            if (i == size) {
                dirs_in_dir = realloc(dirs_in_dir, size * 2 * sizeof(char*));
                size = size * 2;
            }
            dirs_in_dir[i] = malloc(sizeof(char) * (strlen(dirp->d_name) + 1));
            strcpy(dirs_in_dir[i], dirp->d_name);
            ++i;
        }
    }
    closedir(dp);
    qsort(dirs_in_dir, i ,sizeof(char* ), funccmp);
    for (unsigned long long j = 0; j < i; ++j) {
        char fullpath[PATH_MAX + 2];
        snprintf(fullpath, PATH_MAX, "%s/%s", inlet_dir, dirs_in_dir[j]);
        dopath(fullpath, dirs_in_dir[j]);
        free(dirs_in_dir[j]);
    }
    free(dirs_in_dir);
    if (output != NULL) {
        printf("cd ..\n");
    }
}


int main(int argc, char* argv[]) {
    dopath(argv[1], NULL);
}