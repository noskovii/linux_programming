/**
 * Разработать программу solution, которая по заданному pid, осуществляет
 * поиск всех потомков процесса с этим идентификатором и выводит их количество
 * (включая процесс с заданным pid).
 */


#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


void find_processes(int *num, int pid) {
    struct dirent **namelist;
    int n;

    n = scandir("/proc/", &namelist, NULL, alphasort);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    int i;
    char tmp_str[300];
    for (i = 0; i < n; i++) {
        if (atoi(namelist[i]->d_name) && atoi(namelist[i]->d_name) != pid) {
            sprintf(tmp_str, "/proc/%s/stat", namelist[i]->d_name);
            if (namelist[i]->d_type == DT_DIR) {
                FILE *fd = fopen(tmp_str, "r");

                if (fd != NULL) {
                    int tmp_int;
                    char tmp_buf[100];
                    char tmp_chr;
                    int ppid;

                    fscanf(fd, "%d %s %c %d", &tmp_int, tmp_buf,
                        &tmp_chr, &ppid);
                    char name[100];

                    fclose(fd);
                    if (ppid == pid) {
                        *num += 1;
                        int new_pid = atoi(namelist[i]->d_name);
                        find_processes(num, new_pid);
                    }
                }
            }
        }
    }
}

int main(int c, char **v)
{
    int pid = atoi(v[1]);
    int count = 1;

    find_processes(&count, pid);
    printf("%d\n", count);

    return 0;
}

