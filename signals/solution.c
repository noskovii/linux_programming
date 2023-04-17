/* Разработать приложение, умеющее обрабатывать сигналы SIGUSR1 ,SIGUSR2,
 * SIGTERM. После старта Ваше приложение должно по приходу одного из сигналов
 * SIGUSR1,  SIGUSR2 выполнять суммирование числа срабатываний каждого из
 * сигналов, а после прихода сигнала SIGTERM, требуется вывести в стандартный
 * поток вывода 2 числа, разделенных пробелом, соответствующих количеству
 * обработанных сигналов SIGUSR1, SIGUSR2, и завершить программу. Вывод
 * оканчивается символом конца строки.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int num_sig1 = 0;
int num_sig2 = 0;

void int_handler(int signalno) {
    printf("%d %d\n", num_sig1, num_sig2);
    fflush(stdout);
    exit(0);
}

void sig1_handler(int signalno) { num_sig1++; }

void sig2_handler(int signalno) { num_sig2++; }

int main() {
    int c = 0;

    signal(SIGINT, int_handler);
    signal(SIGTERM, int_handler);
    signal(SIGUSR1, sig1_handler);
    signal(SIGUSR2, sig2_handler);

    while (1) {
        usleep(500000);
    }

    return 0;
}
