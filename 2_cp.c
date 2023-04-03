#include <stdlib.h> // General-purpose functions including memory allocation, proccess control and conversion functions
#include <fcntl.h> // constants and prototypes for file control operations
#include <sys/stat.h> // For file permission constants
#include <unistd.h> // For input/output, process management, memory management
#include <stdio.h>

#define BUF_SIZE 100

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage:<FROM> <TO>\n");
        exit(EXIT_FAILURE);
    }

    int from_fd, to_fd;
    
    from_fd = open(argv[1], O_RDONLY);

    if(from_fd == -1)
    {
        printf("An error has occured while opening a file from which to copy data\n");
        exit(EXIT_FAILURE);
    }

    to_fd = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    char buffer[BUF_SIZE];
    ssize_t bytes_read;
    ssize_t bytes_written;

    while ( (bytes_read = read(from_fd, buffer, BUF_SIZE-1)) > 0)
    {
        buffer[bytes_read] = '\0';
        bytes_written = write(to_fd, buffer, bytes_read);
        if(bytes_written == -1)
        {
            printf("Error occured while writing data to a file");
            exit(EXIT_SUCCESS);
        }
    }

    if(close(from_fd))
    {
        printf("An error occured while closing a file from which copy was made");
        exit(EXIT_FAILURE);
    }
    
    if(close(to_fd))
    {
        printf("An error occured while closing a file from which copy was made");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}