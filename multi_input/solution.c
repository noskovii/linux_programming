/**
 * В текущем каталоге есть 2 канала in1 in2, в которые в случайном порядке
 * поступают числа, которые необходимо просуммировать и вывести окончательную
 * сумму на экран. Сумма выводится в отдельной строке, завершающейся символом
 * конца строки. Признаком окончания подачи символов в каналы является закрытие
 * этих каналов посылающей стороной.
 *
 * Подсказка: для неблокирующего чтения использовать select.
 * Замечание: протокол обмена по каналу текстовый, то есть числа представлены
 * строками.
 */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <unistd.h>

int main() {
    int f1 = open("in1", O_RDONLY | O_NONBLOCK);
    int f2 = open("in2", O_RDONLY | O_NONBLOCK);

    int sum = 0;
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    if (f1 == -1 || f2 == -1) {
        printf("Error with opening pipes\n");
        return 0;
    }

    fd_set read_set;
    bool f1_f = true;
    bool f2_f = true;

    for (;;) {
        fd_set fds;
        int maxfd;
        char buf[256];

        if (!(f1_f || f2_f)) break;

        FD_ZERO(&fds);
        FD_SET(f1, &fds);
        FD_SET(f2, &fds);

        maxfd = f1 > f2 ? f1 : f2;
        int res = select(maxfd + 1, &fds, NULL, NULL, NULL);

        if (FD_ISSET(f1, &fds)) {
            res = read(f1, buf, sizeof(buf));
            if (res > 0) {
                buf[res] = 0;
                sum += atoi(buf);
            } else
                f1_f = false;
        }

        if (FD_ISSET(f2, &fds)) {
            res = read(f2, buf, sizeof(buf));
            if (res > 0) {
                buf[res] = 0;
                sum += atoi(buf);
            } else
                f2_f = false;
        }
    }

    printf("%d\n", sum);
}
