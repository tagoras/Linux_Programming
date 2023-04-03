/*
    This program is an example implementation of a tee command which reads its standard input until end of file
    and writes a copy to standard output as well as a file named in arguments.
*/
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE 1000

int main(int argc, char *argv[])
{
    /*
    The program, which is started in command line, has already inherited 3 file descriptors from the parent process, namely
    STDIN_FILENO, STDOUT_FILENO and STDERR_FILENO. Therefore the first task is to read from the standard input
    */
    if(argc < 2)
    {
        printf("Usage: [-a] <FILENAME>\n");
        exit(EXIT_FAILURE);
    }

    if(strcmp(argv[1], "-a")!=0 && argc >= 3)
    {
        printf("Usage: [-a] <FILENAME>\n");
        exit(EXIT_FAILURE);
    }

    int file_permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    int output_fd;
    if(strcmp(argv[1], "-a") == 0 && argc >= 3)
    {
        printf("Opening file in appending mode\n");
        output_fd = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, file_permissions);
        if(output_fd == -1)
        {
            printf("An error has occurred while trying to open a file named %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        output_fd = open(argv[1], O_WRONLY | O_CREAT, file_permissions);
        if(output_fd == -1)
        {
            printf("An error has occurred while opening a file named %s. Make sure the file with that name exists!\n", argv[1]);
            exit(EXIT_FAILURE);
        }
    }

    char buf[BUFF_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;
    while( (bytes_read = read(STDIN_FILENO, buf, BUFF_SIZE-1)) > 0)
    {
       buf[bytes_read] = '\0';
       bytes_written = write(STDOUT_FILENO, buf, bytes_read);
       if(bytes_written == -1)
       {
            printf("An error has occured while writing, or system is out of memory\n");
            exit(EXIT_FAILURE);
       }

       bytes_written = write(output_fd, buf, bytes_read);
       if(bytes_written == -1)
       {
            printf("An error has occured while writing, or system is out of memory\n");
            exit(EXIT_FAILURE);
       }
    }
    if(bytes_read == -1)
    {
        printf("An error has occured while reading from standard output");
        exit(EXIT_FAILURE);
    }
    printf("Successfully read from standard input and outputted to standard output and chosen file!\n");
    close(output_fd);
    exit(EXIT_SUCCESS);
}