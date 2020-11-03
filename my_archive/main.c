#include "my_tar.h"

int error(char* err_message, int exit_code)
{
    fprintf(stderr, "%s\n", err_message);
    return exit_code;
}

int main(int ac, char** av)
{
    int res = 0;
    int fd_archive;
    tar_options* options = get_opt(ac, av);
    if (options == NULL)
    {
        return (error("Error parsing options", 1));
    }
    fd_archive = open_archive_file(options);
    if (fd_archive < 0)
    {
        delete_options(options);
        return (error("Error parsing archive", 2));
    }

    if (options->create == true)
    {
        res += create_archive(fd_archive, options);
    }

    if (options->add == true)
    {
        res += add_to_archive(fd_archive, options);
    }

    if (options->add_if_u == true)
    {
        res += add_if_modifided(fd_archive, options);
    }

    if (options->extract == true)
    {
        res += extract_archive(av);
    }
    if (options->list == true)
    {
        list_archive(options);
    }

    close(fd_archive);
    delete_options(options);
    return 0;
}