#include <stdio.h>

#include "solution.c"


int main(int argc, char *argv[]) {
    int num = 1;
    int res = stringStat("hello", 10, &num);
    printf("res = %d num = %d\n", res, num);

    return 0;
}

