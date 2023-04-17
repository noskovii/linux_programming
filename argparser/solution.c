/* Требуется написать программу solution, выполняющую разбор опций командной
 * строки и выводящую в стандартный поток вывода символ '+', если набор
 * корректен, или '-' в противном случае.
 *
 * Описание возможных опций:
 *     -q | --query (опциональный, но обязательно требует аргумента)
 *     -i | --longinformationrequest (опциональный)
 *     -v | --version (опциональный)
 */

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int c, char **v) {
    int opindex = 0;
    int opchar = 0;

    struct option opts[] = {
        {"query", required_argument, 0, 'q'},
        {"longinformationrequest", no_argument, 0, 'i'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0},
    };

    int is_correct = 1;
    while (-1 != (opchar = getopt_long(c, v, "q:iv", opts, &opindex))) {
        switch (opchar) {
            case 'q':
            case 'i':
            case 'v':
                break;
            default:
                is_correct = 0;
        }
    }

    printf("%c", is_correct ? '+' : '-');
}
