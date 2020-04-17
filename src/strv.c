#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "strv.h"
#include "macro.h"
#include "debug.h"

/* Constructor of strv. */
char **construct_strv()
{
	char **strv = malloc(STRV_SIZE * sizeof(char *));
	for (int i = 0; i < STRV_SIZE; ++i)
	{
		strv[i] = malloc(STR_SIZE * sizeof(char));
		strcpy(strv[i], "null");
	}
	return strv;
}

/* Deestroyer of strv. */
void destroy_strv(char **strv)
{
	for (int i = 0; i < STRV_SIZE; ++i)
	{
		free(strv[i]);
	}
	free(strv);
}

/* Clear all inner parts of strv. */
void clear_strv(char **strv)
{
	for (int i = 0; i < STRV_SIZE; ++i)
	{
		free(strv[i]);
	}
}

/* Insert a str to a strv at the position i. */
void strv_insert(char **strv, char *str, int i)
{
	for (int j = STRV_SIZE - 1; j > i; --j)
	{
		strcpy(strv[j], strv[j - 1]);
	}
	strcpy(strv[i], str);
}

/* Delete the str at the position i of strv. */
void strv_delete(char **strv, int i)
{
	for (int j = i; j < STRV_SIZE - 1; ++j)
	{
		strcpy(strv[j], strv[j + 1]);
		if (strcmp(strv[j], "null") == 0)
		{
			break;
		}
	}
}

/* Count how many strs strv have. */
int strv_count(char **strv)
{
	int i = 0;
	while (strcmp(strv[i], "null") != 0)
	{
		++i;
	}
	return i;
}

/* Check whether the strv is a complete expression. */
int is_strv_complete(char **strv, int p)
{
	int start_count = 0, end_count = 0;
	for (int i = 0; i < p; ++i)
	{
		if (strv[i][0] == '"')
		{
			while (*last_char(strv[i]) != '"' && i < p)
			{
				if (last_char(strv[i]) != &strv[i][0])
				{
					continue;
				}
				++i;
			}
		}
		if (isupper(strv[i][0]))
		{
			++start_count;
		}
		if (strcmp(strv[i], ".") == 0)
		{
			++end_count;
		}
		if (start_count == end_count)
		{
			return 1;
		}
	}
	return 0;
}

/* Print the strv. */
void print_strv(char **strv)
{
	int i = 0;
	while (strcmp(strv[i], "null") != 0 && i < STRV_SIZE)
	{
		printf("%s ", strv[i++]);
	}
	printf("\n");
}

/* Copy strv2 to strv1. */
void strv_cpy(char **strv1, char **strv2)
{
	int i = 0;
	while (strcmp(strv2[i], "null") != 0)
	{
		strcpy(strv1[i], strv2[i]);
		++i;
	}
	strcpy(strv1[i], "null");
}

/* Insert strv2 to strv1 at the position i. */
int strv_insert_strv(char **strv1, char **strv2, int i)
{
	int j = 0;
	while (strcmp(strv2[j], "null") != 0)
	{
		strv_insert(strv1, strv2[j++], i++);
	}
	return j;
}

/* Return the index of the last str of strv. */
int last_str_index(char **strv)
{
	int i = 0;
	while (strcmp(strv[i], "null") != 0)
	{
		++i;
	}
	return i - 1;
}

/* Return the index of the first str with uppercase capital. */
int first_upper_index(char **strv)
{
	int i = 0;
	while (*last_char(strv[i]) != '.')
	{
		if (isupper(strv[i][0]))
		{
			return i;
		}
		++i;
	}
	return -1;
}

/* Return the index of the second str with uppercase capital outside quote. */
int second_upper_index_outside_quote(char **strv)
{
	int i = 0, start_count = 0, end_count = 0, in_quote = 0;
	while (start_count != end_count || start_count == 0)
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
		else if (isupper(strv[i][0]))
		{
			if (i != 0)
			{
				return i;
			}
			++start_count;
		}
		else if (*last_char(strv[i]) == '.')
		{
			++end_count;
		}
		++i;
	}
	return -1;
}

/* Return the index of the second str with uppercase capital outside list. */
int second_upper_index_outside_list(char **strv)
{
	int i = 0, start_count = 0, end_count = 0;
	while (start_count != end_count || start_count == 0)
	{
		if (isupper(strv[i][0]))
		{
			if (i != 0 && strcmp(strv[i], "List") != 0)
			{
				return i;
			}
			++start_count;
		}
		else if (*last_char(strv[i]) == '.')
		{
			++end_count;
		}
		++i;
	}
	return -1;
}