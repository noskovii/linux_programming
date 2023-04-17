/**
 * Разработайте TCP сервер, предназначенный для сортировки символов в строке.
 * Сервер получает на вход строки, оканчивающиеся символом '\0', сортирует в них
 * символы в порядке убывания ASCII-кодов и отсылает обратно на клиент, в виде
 * строки заканчивающейся '\0'. Завершение работы сервера происходит после
 * получения строки, содержащей только 'OFF'.
 *
 * При старте сервер получает на вход номер порта в качестве параметра командной
 * строки. bind производится на адресе 127.0.0.1
 */

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <sys/socket.h>

struct sockaddr_in local;

int server(int port) {
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    bind(ss, (struct sockaddr *)&local, sizeof(local));
    listen(ss, 5);

    cs = accept(ss, NULL, NULL);

    for (;;) {
        char buf[BUFSIZ];
        int res = read(cs, buf, BUFSIZ);

        if (!strcmp(buf, "OFF")) return 0;

        int i, j;
        char temp;
        for (i = 0; i < strlen(buf) - 1; i++) {
            for (j = 0; j < strlen(buf) - 1 - i; j++) {
                if (buf[j] < buf[j + 1]) {
                    temp = buf[j];
                    buf[j] = buf[j + 1];
                    buf[j + 1] = temp;
                }
            }
        }
        write(cs, buf, strlen(buf));
    }
}

int main(int c, char **v) {
    int port = atoi(v[1]);
    server(port);
}
