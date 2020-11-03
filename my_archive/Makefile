NAME = my_tar

SRCS = *.c

SANITIZE = -g3 -fsanitize=address

CFLAGS = -Wall -Wextra -Werror

all: ${NAME}

${NAME}: main.o get_opt.o arguments_list.o create_file.o conversion.o file_manipulation.o my.o extract_archive.o add_to_archive.o list_archive.o
	gcc ${SANITIZE} ${CFLAGS} main.o get_opt.o arguments_list.o create_file.o conversion.o file_manipulation.o my.o extract_archive.o add_to_archive.o list_archive.o -o ${NAME}

main.o: main.c
	gcc ${SANITIZE} ${CFLAGS} -c main.c

get_opt.o: get_opt.c
	gcc ${SANITIZE} ${CFLAGS} -c get_opt.c

arguments_list.o: arguments_list.c
	gcc ${SANITIZE} ${CFLAGS} -c arguments_list.c

create_file.o: create_file.c
	gcc ${SANITIZE} ${CFLAGS} -c create_file.c

conversion.o: conversion.c
	gcc ${SANITIZE} ${CFLAGS} -c conversion.c

file_manipulation.o: file_manipulation.c
	gcc ${SANITIZE} ${CFLAGS} -c file_manipulation.c

my.o: my.c
	gcc ${SANITIZE} ${CFLAGS} -c my.c

extract_archive.o: extract_archive.c
	gcc ${SANITIZE} ${CFLAGS} -c extract_archive.c

add_to_archive.o: add_to_archive.c
	gcc ${SANITIZE} ${CFLAGS} -c add_to_archive.c

list_archive.o: list_archive.c
	gcc ${SANITIZE} ${CFLAGS} -c list_archive.c
	
clean:
	rm -f *.o

fclean:
	rm -f *.o ${NAME}

re: fclean all

