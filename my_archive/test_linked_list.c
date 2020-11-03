#include <stdlib.h>
#include "my_tar.h"

// линкед лист
// цель: напечатать массив из линкед листов

/*
int main(int ac, char** av)
{
    head* first = NULL;
    head* second = NULL;
    head* third = NULL;
    first = malloc(sizeof(head*));
    second = malloc(sizeof(struct Node));
    third = malloc(sizeof(head*));

    if (ac > 2)
    {
        first->current_elem = atoi(av[1]);
        first->next = second;
        second->current_elem = atoi(av[2]);
        third->current_elem = atoi(av[3]);
        second->next = third;
        third->next = NULL; 
        printf("first current %d\n", first->current_elem);
        printf("first next %d\n", first->next->current_elem);
        printf("second current %d\n", second->current_elem);
        printf("second next %d\n", second->next->current_elem);
    }
    else
    {
        printf("need arguments");
    }
*/
typedef struct List
{
    struct Node *list;
} t_list;

typedef struct Node
{
    char* current_elem;
    struct Node* next;
} head;

head* init()
{
    head* my = malloc(sizeof(head));
    if (my != NULL)
    {
        my->current_elem = NULL;
        my->next = NULL;
    }
    else
    {
        printf("in init");
    }
    return my;
}
// получает указатель (первая *) на структуру head с указателем (вторая *) на нулевую ноду
//void add_to_my_list(head** my_head, char* current_arg)
void add_to_my_list(head** my_head, char* current_arg)
{
    // задаем место для новый ноды
    head* s_curr = malloc(sizeof(head));
    s_curr->current_elem = current_arg;
    // слудующий - это указатель на первый элемент head который пришел в аргумете
    s_curr->next = *my_head;
    // и теперь указатель на головной элемент это текущая нода, структура
    *my_head = s_curr;
}

// [0, 8, 13]
int main(int ac, char** av)
{
    t_list* my_list = malloc(sizeof(t_list));
    // сделала мой список из линкед листов пустым
    head* my_head = init();

    int index = 1;
    if (ac > 2)
    {
        while(index < ac)
        {
            // передает адрес на структуру со структурой-списком внутри
            //add_to_my_list(&(my_list)->list, av[index]);
            add_to_my_list(&my_head, av[index]);
            index++;
        }
    }
    else
    {
        printf("need arguments");
    }
    printf("my list 0 %s\n", my_head->current_elem);
    printf("my list 1 %s\n", my_head->next->current_elem);
    printf("my list 2 %s\n", my_head->next->next->current_elem);
    return 0;
}