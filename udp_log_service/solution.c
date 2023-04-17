/**
 * Разработайте UDP сервер для логирования (сбора и записи) сообщений. Сервер
 * при запуске принимает параметр -- номер порта, на котором будут приниматься
 * запросы. Каждый запрос приходящий к серверу - строка, не превышающая размер
 * 5K. Задача сервера -- выводить приходящие строки в стандартный поток
 * ввода-вывода, завершающиеся символом конца строки.
 *
 * Сервер завершает работу, когда получает строку содержащую только текст 'OFF',
 * и заканчивающуюся символом перевода строки '\n'.
 *
 * Сервер использует локальный адрес 127.0.0.1.
 */

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>

struct sockaddr_in local;

int main(int c, char **v) {
    int port = atoi(v[1]);

    int s = socket(AF_INET, SOCK_DGRAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int res = bind(s, (struct sockaddr *)&local, sizeof(local));

    for (;;) {
        char buf[BUFSIZ];
        int res = read(s, buf, BUFSIZ);
        buf[res] = '\0';
        if (!strncmp(buf, "OFF\n", 4)) break;
        printf("%s\n", buf);
    }
}
