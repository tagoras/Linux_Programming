#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

/*
    The code below is a demonstration of how O_APPEND prevents writing data to a file at a specfied position.
    Even if you use lseek() and seek to a specific position and then write, because O_APPEND is specified,
    it will reset the offset of the file description to the first unwritten byte. This, however, can be 
    avoided by using pwrite()
*/

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    int fd;
    if((fd = open("test.txt", O_APPEND | O_WRONLY)) == -1)
    {
        printf("Error while opening a file\n");
        exit(EXIT_FAILURE);
    }

    off_t offset;
    offset = lseek(fd, 0, SEEK_SET);
    if(offset == -1)
    {
        printf("Error while seeking to the beginning of the file\n");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    ssize_t bytes_read;

    if((bytes_read = read(STDIN_FILENO, buf, BUF_SIZE-1)) <= 0)
    {
        printf("Error occured while reading data from standard input\n");
        exit(EXIT_FAILURE);
    }
    printf("%ld bytes have been read from standard input", bytes_read);
    buf[bytes_read] = '\0';

    ssize_t bytes_written;
    if((bytes_written = write(fd, buf, bytes_read)) == -1)
    {
        printf("Error while writing to file\n");
        exit(EXIT_FAILURE);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}