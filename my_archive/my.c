#include "my_tar.h"

char* my_strncpy(char* dest, char* src, int num)
{
    int index;
    index = 0;
    while (index < num && src[index] != '\0')
    {
        dest[index] = src[index];
        index++;
    }
    dest[index] = '\0';
    return dest;
}

void my_memset(char* buff, char c, int size)
{
    int index;
    index = 0;
    while (index < size)
    {
        buff[index] = c;
        index += 1;
    }
}

void my_bzero(char* buff, int size)
{
    my_memset(buff, 0, size);
}

char* my_init(int size)
{
    char* buff = (char*)malloc(size);
    my_bzero(buff, size);
    return buff;
}

int my_strcmp(char* a, char* b)
{
    int count;

    count = 0;
    while (a[count] != '\0' && b[count] != '\0' && a[count] == b[count])
        count++;
    return (a[count] - b[count]);
}

int my_strlen(char* str)
{
    int index;
    index = 0;
    while (str[index] != '\0')
    {
        index += 1;
    }
    return index;
}

char* my_strdup(char* str)
{
    int index;
    int length;
    char* my_str;

    length = my_strlen(str);
    my_str = (char*)malloc(sizeof(char) * length + 1);
    if (!my_str)
    {
        return 0;
    }
    index = 0;
    while (str[index] != '\0')
    {
        my_str[index] = str[index];
        index += 1;
    }
    my_str[index] = '\0';
    return my_str;
}

char* my_join(char* first_part, char* second_part, char* third_part)
{
    char* new_str;
    int size =
        strlen(first_part) + strlen(second_part) + strlen(third_part) + 1;
    new_str = malloc(sizeof(char) * size);
    int index;
    int index_2;
    int index_3;
    index = 0;
    while (first_part[index] != '\0')
    {
        new_str[index] = first_part[index];
        index++;
    }
    index_2 = 0;
    while (second_part[index_2] != '\0')
    {
        new_str[index] = second_part[index_2];
        index++;
        index_2++;
    }
    index_3 = 0;
    while (third_part[index_3] != '\0')
    {
        new_str[index] = third_part[index_3];
        index++;
        index_3++;
    }
    new_str[index] = '\0';
    return new_str;
}