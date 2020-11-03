#include "my_tar.h"

void print_list(tar_options *options)
{
    int pos;

    tar_header archive_header;

    int fd_file = open(options->archive_name, O_RDONLY);
    int arch_size = get_file_size(fd_file); // ok
    int end_of_arch = arch_size - (BLOCKSIZE * 2); // ok

    char buf[BLOCKSIZE];

    pos = 0;

    while (pos < end_of_arch)
    {
        lseek(fd_file, pos, SEEK_SET);
        read(fd_file, buf, 100);
        my_strncpy(archive_header.name, buf, 100);
        
        printf("%s\n", buf);

        lseek(fd_file, pos + 124, SEEK_SET);
        read(fd_file, buf, 12);
        my_strncpy(archive_header.size, buf, 12);

        pos = calc_next_position(pos, archive_header);
    }
}

void print_unfound_files(header_node* args_list)
{
    while (args_list != NULL)
    { 
        if (args_list->should_add == false)
        {
            printf("tar: %s: Not found in archive\n", args_list->value.name);
            printf("tar: Exiting with failure status due to previous errors\n");
            return;
        }
        args_list = args_list->next;
    }
}

void init_should_add(header_node* args_list)
{
    while (args_list != NULL)
    {
        args_list->should_add = false;
        args_list = args_list->next;
    }
}

void check_arg_in_archive(header_node* args_list, tar_header arch_current_header)
{
    int index;
    index = 0;
    while (args_list != NULL)
    {
        if (my_strcmp(args_list->value.name, arch_current_header.name) == 0)
        {
            args_list->should_add = true;
            printf("%s\n", args_list->value.name);
            index++;
        }
        args_list = args_list->next;
    }
}

void print_args_in_arch(tar_options *options)
{
    int pos;

    tar_header archive_header;
    header_node* headers_arg_list = NULL;
    headers_arg_list = options_to_headers(options);
    header_node* copy_headers_arg_list = headers_arg_list;

    init_should_add(headers_arg_list);

    int fd_file = open(options->archive_name, O_RDONLY);
    int arch_size = get_file_size(fd_file); // ok
    int end_of_arch = arch_size - (BLOCKSIZE * 2); // ok

    char buf[BLOCKSIZE];

    pos = 0;
    
    while (pos < end_of_arch)
    {
        lseek(fd_file, pos, SEEK_SET);
        read(fd_file, buf, 100);
        my_strncpy(archive_header.name, buf, 100);


        lseek(fd_file, pos + 124, SEEK_SET);
        read(fd_file, buf, 12);
        my_strncpy(archive_header.size, buf, 12);

        check_arg_in_archive(headers_arg_list, archive_header);
        
        pos = calc_next_position(pos, archive_header);
    }
    print_unfound_files(headers_arg_list);
    free_list(copy_headers_arg_list);
}

void list_archive(tar_options *options)
{
    if (options->args->filename != NULL)
    {
        print_args_in_arch(options);
    }
    else if (options->args->filename == NULL)
    {
        print_list(options);
    }
}