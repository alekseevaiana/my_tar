#include <fcntl.h>
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

int open_archive_file(tar_options* options)
{
    int fd_archive;
    int flags = O_RDONLY;
    const mode_t DEFAULT_CREAT_MODE = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (options->create)
        flags = O_CREAT | O_WRONLY | O_TRUNC;
    else if (options->extract || options->list)
        flags = O_RDONLY;
    else if (options->add || options->add_if_u)
        flags = O_RDONLY | O_WRONLY;

    fd_archive = open(options->archive_name, flags, DEFAULT_CREAT_MODE);
    return fd_archive;
}