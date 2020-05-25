#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>


int main() {
    unsigned long long result = 0;
    unsigned long long first;
    unsigned long long second;
    char rest_of_the_line[4096];
    while(scanf("%llx-%llx", &first, &second) == 2) {
        result += second - first;
        scanf("%s%*[^\n]", rest_of_the_line);
    }
    printf("%llu", result);
}