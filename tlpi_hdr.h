#ifndef TLPI_HDR_H
#define TLPI_HDR_H // Header guards prevent double inclusion

#include <sys/types.h> // Type definitions used by many programs
#include <stdio.h> // Standared I/O functions
#include <stdlib.h> /* Prototypes of comonly used library functions, 
plus EXIT_SUCCESS and EXIT_FAILURE constants*/

#include <unistd.h> // Prototypes for many system calls
#include <errno.h> // Declares errno and defines error constants
#include <string.h> // Commonly used string-handling functions

#include "get_num.h"// Declares functions for handling numeric arguments

#include "error_functions.h" // Declares custom error handling functions

typedef enum {FALSE, TRUE} Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

#endif
