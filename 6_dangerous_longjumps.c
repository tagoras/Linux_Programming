#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

/*
    A quick demonstration of a segfault that occurs because of an attempt to jump to a function that has already returned
*/

static jmp_buf env;

int f1()
{
    int res = setjmp(env);
    if(res == 1)
    {
        printf("This was caused by a proper longjump");
        return 1;
    }
    return 2;
}

int main(int argc, char *argv[]) 
{
    f1();
    longjmp(env, 1);
    return 0;
}