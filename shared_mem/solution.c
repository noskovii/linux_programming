/**
 * В системе существуют 2 региона разделяемой памяти, заполненной некоторыми
 * числами (типа int). Каждый из регионов имеет размер 1000 байт. Вам требуется
 * разработать приложение, которое попарно суммирует первые 100 чисел в этих
 * регионах и помещает суммы в новый (созданный вашим приложением) регион памяти
 * размером 1000 байт. Таким образом, после завершения работы Вашего приложения
 * в памяти должен существовать регион разделяемой памяти размером 1000 байт,
 * содержащий в начале 100 сумм. Перед завершением работы приложение выводит в
 * стандартный поток ввода-вывода ключ созданного региона, завершающийся
 * символом конца строки. На вход ваше приложение принимает ключи существующих
 * регионов памяти.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

int main(int c, char **v) {
    int sh1_key = atoi(v[1]);
    int sh2_key = atoi(v[2]);
    int res_key = 54321;

    int shmid_1;
    if ((shmid_1 = shmget(sh1_key, 1000, 0660 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    int shmid_2;
    if ((shmid_2 = shmget(sh2_key, 1000, 0660 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    int *sh1 = (int *)shmat(shmid_1, NULL, 0600 | IPC_CREAT);
    int *sh2 = (int *)shmat(shmid_2, NULL, 0600 | IPC_CREAT);

    int mas[100];
    int i;
    for (i = 0; i < 100; i++) {
        mas[i] = *sh1 + *sh2;
        sh1++;
        sh2++;
    }

    int shmid;
    if ((shmid = shmget(res_key, 1000, 0666 | IPC_CREAT)) == -1) {
        perror("shmget");
        exit(1);
    }

    int *sh_res = (int *)shmat(shmid, NULL, 0);
    for (i = 0; i < 100; i++) {
        *sh_res = mas[i];
        sh_res++;
    }

    printf("%d\n", res_key);
}
