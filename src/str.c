#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fundotlib.h"
#include "strv.h"
#include "str.h"
#include "debug.h"

/* Get the pointer to the last char of a str. */
char *get_last_char(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i + 1] == '\0')
        {
            return &s[i];
        }
        ++i;
    }
    return NULL;
}

/* Provide the information of a str. */
int str_info(char *s)
{
    if (isupper(s[0]))
    {
        return 0;
    }
    else if (*get_last_char(s) == '.')
    {
        return 1;
    }
    else if (*get_last_char(s) == ':')
    {
        return 2;
    }
    return -1;
}

/* Count how many tariling dots the str s has. */
int end_dot_count(char *s)
{
    int i = 0;
    while (s[i++] != '\0')
        ;
    i -= 2;
    int count = 0;
    while (i >= 0 && s[i--] == '.')
    {
        ++count;
    }
    return count;
}