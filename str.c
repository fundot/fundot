#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "fundotlib.h"
#include "strv.h"
#include "str.h"
#include "debug.h"

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

int first_upper_index(char **strv)
{
    int i = 0;
    while (*get_last_char(strv[i]) != '.')
    {
        if (str_info(strv[i]) == 0)
        {
            return i;
        }
        ++i;
    }
    return -1;
}

int second_upper_index_outside_quote(char **strv)
{
    int i = 0, start_word_count = 0, end_word_count = 0, in_quote = 0;
    while (start_word_count != end_word_count || start_word_count == 0)
    {
        if (in_quote == 1)
        {
            if (strcmp(strv[i], "\"") == 0)
            {
                in_quote = 0;
            }
        }
        else if (strcmp(strv[i], "\"") == 0)
        {
            in_quote = 1;
        }
        else if (str_info(strv[i]) == 0)
        {
            if (i != 0)
            {
                return i;
            }
            ++start_word_count;
        }
        else if (*get_last_char(strv[i]) == '.')
        {
            ++end_word_count;
        }
        ++i;
    }
    return -1;
}

int second_upper_index_outside_list(char **strv)
{
    int i = 0, start_word_count = 0, end_word_count = 0;
    while (start_word_count != end_word_count || start_word_count == 0)
    {
        if (str_info(strv[i]) == 0)
        { 
            if (i != 0 && strcmp(strv[i], "List") != 0)
            {
                return i;
            }
            ++start_word_count;
        }
        else if (*get_last_char(strv[i]) == '.')
        {
            ++end_word_count;
        }
        ++i;
    }
    return -1;
}