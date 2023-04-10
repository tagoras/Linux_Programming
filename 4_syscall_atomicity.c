#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
    This program provides an example why atomicity is an important property in linux applications
    if you run the program using: ./a.out 1.txt 1000000 & ./a.out 1.txt 1000000 then 2000000 bytes will be written appropriately
    since O_APPEND flag is specified (any read is set to the first unwritten byte)

    However, if 4 arguments are specified then O_APPEND flag is removed and the program instead uses custom seek to the end of the file. This, if
    run by two different programs simultaneously, will create a run condition.

    Run:
    ./a.out 1.txt 1000000 & ./a.out 1.txt 1000000
    ./a.out 2.txt 1000000 x & ./a.out 2.txt 1000000 x
    ls -l (to see how the sizes of the files do not match)
*/

int main(int argc, char *argv[])
{
    if(argc == 3)
    {
        int fd;
        if((fd = open(argv[1], O_CREAT | O_APPEND | O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
        {
            printf("Error while opening a file");
            exit(EXIT_FAILURE);
        }
        int byte_count = atoi(argv[2]);

        char buf = 'A';

        while (byte_count)
        {
            if(write(fd, &buf, 1) != 1)
            {
                printf("Bad write");
                exit(EXIT_FAILURE);
            }
            --byte_count;
        }
        if(close(fd) == -1)
        {
            printf("Error while closing the file");
        }

        exit(EXIT_SUCCESS);
    }

    else if(argc == 4)
    {
        int fd;
        if((fd = open(argv[1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR)) == -1)
        {
            printf("Error while opening a file");
            exit(EXIT_FAILURE);
        }
        int byte_count = atoi(argv[2]);

        char buf = 'A';
        off_t seek_location;

        while (byte_count)
        {
            seek_location = lseek(fd, 0, SEEK_END);
            if(seek_location == -1)
            {
                printf("Unsuccessful seek to the end of the file");
                exit(EXIT_FAILURE);
            }
            if(write(fd, &buf, 1) != 1)
            {
                printf("Bad write");
                exit(EXIT_FAILURE);
            }
            --byte_count;
        }
        if(close(fd) == -1)
        {
            printf("Error while closing the file");
        }

        exit(EXIT_SUCCESS);
    }
}