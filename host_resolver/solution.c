/* Разработайте утилиту командной строки, принимающую на вход имя хоста и
 * печатающую в стандартный поток вывода список IP-адресов, ассоциированных с
 * данным именем.
 */

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

int main(int c, char **v) {
    if (c != 2) return -1;

    struct hostent *h;
    h = gethostbyname(v[1]);

    if (NULL == h) {
        printf("Error\n");
        return -1;
    }

    int i = 0;
    while (NULL != h->h_addr_list[i]) {
        struct in_addr *a = (struct in_addr *)h->h_addr_list[i];
        printf("%s\n", inet_ntoa(*a));
        i++;
    }
}
