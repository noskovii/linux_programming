/*
 * Разработать программу solution, которая осуществляет поиск и подсчет числа
 * процессов с именем genenv в системе Linux на которой выполняется программа.
 */

#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
    int pid;
    char *str = "genenv";
    struct dirent **namelist;
    int n;

    n = scandir("/proc/", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    int num = 0;
    int i;
    char tmp_str[300];

    for (i = 0; i < n; i++) {
        if (atoi(namelist[i]->d_name)) {
            sprintf(tmp_str, "/proc/%s/stat", namelist[i]->d_name);

            if (namelist[i]->d_type == DT_DIR) {
                FILE *fd = fopen(tmp_str, "r");
                int tmp_int;
                char tmp_buf[100];
                char tmp_chr;
                int ppid;

                fscanf(fd, "%d %s %c %d", &tmp_int, tmp_buf, &tmp_chr, &ppid);
                char name[100];

                if (strstr(tmp_buf, str) != NULL) num++;
            }
        }
        free(namelist[i]);
    }

    free(namelist);
    printf("%d\n", num);
}
