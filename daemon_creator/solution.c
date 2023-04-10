#include <unistd.h>
#include <stdio.h>


int main()
{
    daemon(1, 1);
    int pid = getpid();
    printf("%d\n", pid);
    sleep(1000);
}

