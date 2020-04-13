#include <stdio.h>
#include "debug.h"
#include "macro.h"

/* Show in terminal that a breakpoint is running. */
void print_running()
{
    printf("RUNNING\n");
}

/* Print half of a strv including "null". */
void print_half_strv(char **strv)
{
    for (int i = 0; i < STRV_SIZE / 2; ++i)
    {
        printf("%s ", strv[i]);
    }
    printf("\n");
}