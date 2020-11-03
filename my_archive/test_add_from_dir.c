#include "my_tar.h"

int is_directory(char* name)
{
    struct stat current_file;
    if (stat(name, &current_file) == 0)
    {
        if (S_ISDIR(current_file.st_mode))
        {
            return 1;
        }
    }
    return 0;
}

// first arg is a head node type is t_argument (address)
void put_file_to_list(t_argument** t_arg, char* filename)
{
    struct dirent* dir_info;
    add_to_list(t_arg, filename);
    char* path;
    if (is_directory(filename))
    {
        DIR* dir = opendir(filename);
        while (((dir_info = readdir(dir)) != NULL))
        {
            if (dir_info->d_name[0] != '.')
            {
                // dir_info->d_name - the current name of file or dir inside
                // filenama(dirname)
                path = my_join(filename, "/", dir_info->d_name);
                put_file_to_list(t_arg, path);
            }
        }
    }
}

int main(int ac, char** av)
{
    t_argument* head = init_argument();
    put_file_to_list(&head, av[1]);
    printf("head is %s\n", head->filename);
    printf("head is %s\n", head->next->filename);
    printf("head is %s\n", head->next->next->filename);
    printf("head is %s\n", head->next->next->next->filename);
    return 0;
}