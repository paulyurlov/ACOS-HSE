#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct Values
{
    unsigned char args[64];
};


int main(int argc, char* argv[]) {
    void * opened_lib = dlopen(argv[1], RTLD_NOW);
    void *opened_func = dlsym(opened_lib, argv[2]);
    struct Values arg;
    int memory = 0;
    for (int i = 1; i < strlen(argv[3]); ++i) {
        if (argv[3][i] == 'i') {
            int inlet = (int)strtol(argv[3 + i], NULL, 10);
            memcpy(arg.args + memory, &inlet, sizeof(int));
            memory += sizeof(int);
        } else {
            if (argv[3][i] == 'd') {
                double inlet = strtod(argv[3 + i], NULL);
                memcpy(arg.args + memory, &inlet, sizeof(double ));
                memory += sizeof(double );
            } else {
                memcpy(arg.args + memory, argv + (3 + i), sizeof(char *));
                memory += sizeof(char *);
            }
        }
    }
    if (argv[3][0] == 'v') {
        ((void(*)(struct Values))opened_func)(arg);
    }
    if (argv[3][0] == 'i') {
        printf("%d\n", ((int(*)(struct Values))opened_func)(arg));
    }
    if (argv[3][0] == 'd') {
        printf("%.10g\n", ((double (*)(struct Values))opened_func)(arg));
    }
    if (argv[3][0] == 's') {
        printf("%s\n", ((char*(*)(struct Values))opened_func)(arg));
    }
    dlclose(opened_lib);
    return 0;
}