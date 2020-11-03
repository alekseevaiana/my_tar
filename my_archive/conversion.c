#include "my_tar.h"

int my_iterative_pow(int a, int b)
{
    int res = 1;
    for (int i = 0; i != b; i++)
    {
        res = res * a;
    }
    return res;
}

long oct_to_dec(long oct)
{
    int dec = 0;
    int i = 0;

    while (oct != 0)
    {
        dec += (oct % 10) * my_iterative_pow(8, i);
        i++;
        oct /= 10;
    }
    return dec;
}

long dec_to_oct(long dec)
{
    int oct = 0;
    int i = 0;

    while (dec != 0)
    {
        oct += (dec % 8) * my_iterative_pow(10, i);
        i++;
        dec /= 8;
    }
    return oct;
}

char *my_itoa_base(char *res, unsigned int number, int size, int base)
{
    const char symbols[] = "0123456789ABCDEF";
    memset(res, '0', size - 1);
    res[size - 1] = '\0';
    size--;
    while (number)
    {
        res[--size] = symbols[number % base];
        number /= base;
    }
    return res;
}

long my_atol(const char *str, int size)
{
    long res = 0;
    int i = 0;
    while (str[i] && i < size && str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}

long my_atoi(char *str)
{
    long res = 0;
    int i = 0;
    int size = my_strlen(str);
    while (str[i] && i < size && str[i] >= '0' && str[i] <= '9')
    {
        res = res * 10 + (str[i] - '0');
        i++;
    }
    return res;
}