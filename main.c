#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#include "include/tokens.h"

#define MAX_PROGRAM_LEN_BYTES 1024 /* 1024 bytes -> 1 KB */

int main() {
    FILE *fptr;

    fptr = fopen("test.hug", "r");

    char file_buffer[MAX_PROGRAM_LEN_BYTES];

    fgets(file_buffer, MAX_PROGRAM_LEN_BYTES, fptr); /* 1 KB offset */

    // printf("%s", file_buffer);
    
    fclose(fptr);

    return 0;

}