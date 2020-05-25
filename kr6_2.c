#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <dlfcn.h>


int main(int argc, char* argv[]) {
    float x = atof(argv[1]);
    char* first_library = argv[2];
    for (int i = 2; i < argc - 1; i+=2) {
        char* func = argv[i + 1];
        char* library = argv[i];
        if (strlen(library) == 1) {
            library = first_library;
        }
        void * opened_lib = dlopen(library, RTLD_NOW);
        if (!opened_lib) {
            continue;
        }
        void *opened_func = dlsym(opened_lib, func);
        if (!opened_func) {
            dlclose(opened_lib);
            continue;
        }
        x = ((float (*)(float)) opened_func)(x);
        dlclose(opened_lib);
        first_library = library;
    }
    printf("%.6g\n", x);
}