/**
 * Разработать программу solution, которая по заданному pid, осуществляет
 * поиск пути в дереве процессов до процесса с идентификатором 1 (init).
 * Для каждого найденного процесса печатается в отдельной строке его
 * идентификатор.
 */


#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


void print_process_parents(int pid);

int main(int c, const char **v) {
    int pid = atoi(v[1]);
    print_process_parents(pid);
}

int get_parent_pid(int current) {
    char tmp_str[100];
    sprintf(tmp_str, "/proc/%d/stat", current);

    FILE *fd = fopen(tmp_str, "r");
    int tmp_int;
    char tmp_buf[100];
    char tmp_chr;
    int ppid;

    fscanf(fd, "%d %s %c %d", &tmp_int, tmp_buf, &tmp_chr, &ppid);
    return ppid;
}

void print_process_parents(int pid) {
    pid_t current = pid;

    while (current != 1 ) {
        printf("%d\n",current);
        current = get_parent_pid(current);
    }

    printf("1\n");
}

