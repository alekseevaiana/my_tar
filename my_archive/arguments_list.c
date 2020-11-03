#include <stdio.h>
#include "my_tar.h"

t_argument *init_argument()
{
    t_argument *t_arg = malloc(sizeof(t_argument));
    if (t_arg != NULL)
    {
        t_arg->filename = NULL;
        t_arg->next = NULL;
    }
    else
    {
        printf("FAILURE");
        exit(1);
    }
    return t_arg;
}

void add_to_list(t_argument **t_arg, char *current_file)
{
    t_argument *arg = malloc(sizeof(t_argument));
    arg->filename = current_file;
    arg->next = (*t_arg);
    *t_arg = arg;
}

// first arg is a head node type is t_argument (address)
void put_file_to_list(t_argument **t_arg, char *filename)
{
    struct dirent *dir_info;
    add_to_list(t_arg, filename);
    char *path;
    if (is_directory(filename))
    {
        DIR *dir = opendir(filename);
        while (((dir_info = readdir(dir)) != NULL))
        {
            if (dir_info->d_name[0] != '.')
            {
                path = my_join(filename, "/", dir_info->d_name);
                put_file_to_list(t_arg, path);
            }
        }
        closedir(dir);
    }
}

void delete_argument_list(t_argument **ptr)
{
    t_argument *current = *ptr;
    t_argument *next;

    while (current != NULL)
    {
        next = current->next;
        free(current->filename);
        free(current);
        current = next;
    }
}