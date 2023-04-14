/**
 * Разработать программу solution, которая осуществляет поиск родительского
 * PID текущего процесса в файловой системе proc и выводит найденное значение
 * на консоль. Результат, возвращаемый функций должен быть выведен отдельной
 * строкой (должен оканчиваться символом перевода строки \n) в stdio.
 */


#include <stdio.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
  int pid;
  int cur_pid = getpid();
  int parent_pid = getppid();

  char str[100];
  sprintf(str, "/proc/%d/stat", cur_pid);

  FILE *fd = fopen(str, "r");

  int tmp_int;
  char tmp_buf[100];
  char tmp_chr;
  int ppid;

  fscanf(fd, "%d %s %c %d", &tmp_int, tmp_buf, &tmp_chr, &ppid);

  printf("%d\n", ppid);
}
