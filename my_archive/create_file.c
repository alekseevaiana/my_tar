#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include "my_tar.h"

tar_header *init_tar_header()
{
    tar_header *header = malloc(sizeof(tar_header));
    if (header != NULL)
    {
        my_bzero((char *)header, sizeof(tar_header));
    }

    return header;
}

int get_permission(int mode)
{
    int perm_tar;
    perm_tar = 0;
    if (mode & S_IXOTH)
    {
        perm_tar = perm_tar | TOEXEC;
    }
    if (mode & S_IWOTH)
    {
        perm_tar = perm_tar | TOWRITE;
    }
    if (mode & S_IROTH)
    {
        perm_tar = perm_tar | TOREAD;
    }
    if (mode & S_IXGRP)
    {
        perm_tar = perm_tar | TGEXEC;
    }
    if (mode & S_IWGRP)
    {
        perm_tar = perm_tar | TGWRITE;
    }
    if (mode & S_IRGRP)
    {
        perm_tar = perm_tar | TGREAD;
    }
    if (mode & S_IXUSR)
    {
        perm_tar = perm_tar | TUEXEC;
    }
    if (mode & S_IWUSR)
    {
        perm_tar = perm_tar | TUWRITE;
    }
    if (mode & S_IRUSR)
    {
        perm_tar = perm_tar | TUREAD;
    }
    return perm_tar;
}

int check_sum(tar_header *header)
{
    int index;
    int result;
    result = 0;
    for (index = 0; index < 500; ++index)
    {
        if (index < 148 || index > 155)
        {
            result += ((unsigned char *)header)[index];
        }
        else
        {
            result += 0x20;
        }
    }
    return result;
}

char get_typeflag(int mode)
{
    switch (mode & S_IFMT)
    {
        case S_IFREG:
            return REGTYPE;
        case S_IFLNK:
            return SYMTYPE;
        case S_IFCHR:
            return CHRTYPE;
        case S_IFBLK:
            return BLKTYPE;
        case S_IFDIR:
            return DIRTYPE;
        case S_IFIFO:
            return FIFOTYPE;
        default:
            return REGTYPE;
    }
}

char *chksum_str(char *number_str, char *dest, int num)
{
    int index;
    index = 0;
    while (index < num && number_str[index] != '\0')
    {
        dest[index] = number_str[index];
        index++;
    }
    dest[index] = '\0';
    dest[index + 1] = ' ';
    return dest;
}

tar_header *get_metadata(char *filename)
{
    tar_header *header = init_tar_header();

    struct stat info;

    if (lstat(filename, &info) < 0)
    {
        printf("Error opening file\n");
        return NULL;
    }

    struct passwd *p;
    struct group *g;
    gid_t gid = info.st_gid;
    uid_t uid = info.st_uid;
    if ((p = getpwuid(uid)) == NULL)
    {
        printf("getpwuid() error");
    }
    else
    {
        my_strncpy(header->uname, p->pw_name, 32);
    }
    if ((g = getgrgid(gid)) == NULL)
    {
        printf("getgrgid() error");
    }
    else
    {
        my_strncpy(header->gname, g->gr_name, 32);
    }
    char chksum_res[8];
    header->typeflag = get_typeflag(info.st_mode);
    if (header->typeflag == '5')
    {
        my_strncpy(header->name, filename, 100);
    }
    else
    {
        my_strncpy(header->name, filename, 100);
    }
    my_strncpy(header->magic, "ustar ",
               TMAGLEN);  // hardcode for apace after magic
    my_strncpy(header->version, " ", 2);
    my_itoa_base(header->mtime, info.st_mtime, 12, OCTAL_BASE);
    my_itoa_base(header->mode, get_permission(info.st_mode), 8, OCTAL_BASE);
    my_itoa_base(header->uid, info.st_uid, 8, OCTAL_BASE);
    my_itoa_base(header->gid, info.st_gid, 8, OCTAL_BASE);
    my_itoa_base(header->size, info.st_size, 12, OCTAL_BASE);
    my_itoa_base(chksum_res, check_sum(header), 7, OCTAL_BASE);
    chksum_str(chksum_res, header->chksum,
               8);  // hardcoded for the space after chksum
    return header;
}

int get_file_size(int fd)
{
    int res = 0;
    int reader = 0;
    char buf[BLOCKSIZE];

    while ((reader = read(fd, buf, BLOCKSIZE)) > 0)
    {
        res += reader;
    }

    if (res % BLOCKSIZE != 0)
    {
        res += BLOCKSIZE - (res % BLOCKSIZE);
    }

    lseek(fd, 0, SEEK_SET);
    return res;
}

int write_file_content(int fd_archive, char *filename)
{
    int res = 0;

    int fd_file = open(filename, O_RDONLY);
    int file_size = get_file_size(fd_file);

    char content[file_size];
    my_bzero(content, file_size);
    read(fd_file, content, file_size);
    res += write(fd_archive, content, file_size);
    close(fd_file);
    return res;
}

void end_of_archive(int fd)
{
    char end[BLOCKSIZE * 2];
    my_bzero(end, BLOCKSIZE * 2);
    write(fd, end, BLOCKSIZE * 2);
    return;
}

int create_archive(int fd_archive, tar_options *options)
{
    int res = 0;
    char buf[12];
    t_argument *current_arg = options->args;
    tar_header *header;
    while (current_arg->filename != NULL)
    {
        header = get_metadata(current_arg->filename);

        if (header != NULL)
        {
            if (header->typeflag == '5')
            {
                write(fd_archive, header, sizeof(tar_header));
                my_bzero(buf, 12);
                lseek(fd_archive, 12, SEEK_CUR);
                free(header);
            }
            else
            {
                write(fd_archive, header, sizeof(tar_header));
                my_bzero(buf, 12);
                lseek(fd_archive, 12, SEEK_CUR);
                write_file_content(fd_archive, current_arg->filename);
                free(header);
            }
        }
        else
        {
            res++;
        }
        current_arg = current_arg->next;
    }

    end_of_archive(fd_archive);

    return res;
}