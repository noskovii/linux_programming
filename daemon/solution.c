/**
 * Разработать программу solution, которая при запуске себя "демонизирует"
 * и остается в  памяти. Перед закрытием стандартного потока вывода stdout
 * унаследованного от родителя, программа должна вывести в него pid
 * процесса-демона. Снабдить демон обработчиком сигнала SIGURG, по приходу
 * которого демон должен завершать свою работу.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signalno) { exit(0); }

int main() {
    daemon(1, 1);
    int pid = getpid();
    printf("%d\n", pid);
    signal(SIGURG, handler);

    for (;;) {
        sleep(1000);
    }
}
