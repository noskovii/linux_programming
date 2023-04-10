#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <dlfcn.h>
#include <stdlib.h>


int (*function)(int);

bool init_library(char *lib_name, char *func_name)
{
    char *lib = (char*)malloc(sizeof(lib_name));
    sprintf(lib, "./%s", lib_name);

    void *hdl = dlopen(lib, RTLD_LAZY);
    if (NULL == hdl)
        return false;

    function = (int (*)(int))dlsym(hdl, func_name);
    if (NULL == function)
        return false;

    return true;
}

int main (int argc, char * argv[])
{
    char *lib_name = argv[1];
    char *func_name = argv[2];
    int param = atoi(argv[3]);

    init_library(lib_name, func_name);

    int res = function(param);
    printf("%d\n", res);

    return 0;
}

