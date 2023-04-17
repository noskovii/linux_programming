/**
 * Создать разделяемую динамическую библиотеку libsolution.so в которой
 * реализовать функцию со следующим прототипом:
 *     int stringStat(const char *string, size_t multiplier, int *count);
 *
 * Функция возвращает значение длины строки string, умноженное на multiplier,
 * и увеличивает на 1 значение, на которое указывает count.
 */

#include "solution.h"

#include <string.h>

int stringStat(const char *string, size_t multiplier, int *count) {
    *count = *count + 1;
    return strlen(string) * multiplier;
}
