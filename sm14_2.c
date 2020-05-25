#include <stdio.h>
#include <dlfcn.h>

int main(int argc, char* argv[]) {
    char* func = argv[1];
    double x;
    void * opened_lib = dlopen("/lib/libm.so.6", RTLD_NOW);
    void *opened_func = dlsym(opened_lib, func);
    while(scanf("%lf", &x) == 1) {
        x = ((double (*)(double)) opened_func)(x);
        printf("%.10g\n", x);
    }
    dlclose(opened_lib);
    return 0;
}
