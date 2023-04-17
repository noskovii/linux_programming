/**
 * Разработать программу solution, обеспечивающую загрузку динамической
 * библиотеки в режиме исполнения. При запуске, программе передается имя
 * динамической библиотеки, имя функции которая должна быть вызвана, и ее
 * аргумент. Функция в библиотеке принимает на вход int и возвращает int.
 * Результат, возвращаемый функцией должен быть выведен отдельной строкой
 * (оканчиваться символом новой строки \n) в stdout.
 */

#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int (*function)(int);

bool init_library(char *lib_name, char *func_name) {
    char *lib = (char *)malloc(sizeof(lib_name));
    sprintf(lib, "./%s", lib_name);

    void *hdl = dlopen(lib, RTLD_LAZY);
    if (NULL == hdl) return false;

    function = (int (*)(int))dlsym(hdl, func_name);
    if (NULL == function) return false;

    return true;
}

int main(int argc, char *argv[]) {
    char *lib_name = argv[1];
    char *func_name = argv[2];
    int param = atoi(argv[3]);

    init_library(lib_name, func_name);

    int res = function(param);
    printf("%d\n", res);

    return 0;
}
