#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int new_fd;
    new_fd = dup(STDIN_FILENO);
    if(new_fd == -1)
    {
        printf("An error has occured while duplicating a file descriptor\n");
        exit(EXIT_FAILURE);
    }
    if(fcntl(new_fd, F_GETFL) == fcntl(STDIN_FILENO, F_GETFL))
    {
        printf("Open file status flags match!\n");
    }

    if(lseek(new_fd, 0, SEEK_CUR) == lseek(STDIN_FILENO, 0, SEEK_CUR))
    {
        printf("Both file descriptors share the same offset value!\n");
    }

    exit(EXIT_SUCCESS);
}