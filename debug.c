#include <stdio.h>
#include "macro.h"

void print_running()
{
    printf("RUNNING\n");
}

void print_half_strv(char **strv)
{
    for (int i = 0; i < STRV_SIZE / 2; ++i)
    {
        printf("%s ", strv[i]);
    }
    printf("\n");
}