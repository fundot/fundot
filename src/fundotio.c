#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "str.h"
#include "strv.h"
#include "fundotio.h"
#include "macro.h"
#include "debug.h"

/* Read the contents from a file and convert them to a parser-friendly strv. */
char **read_file(char *file_name)
{
	FILE *file = fopen(file_name, "r");
	char **strv = construct_strv();
	int i = 0;
	while (i < STRV_SIZE)
	{
		char *s = malloc(STR_SIZE * sizeof(char));
		fscanf(file, "%s", s);
		strcpy(strv[i], s);
		free(s);
		if (strv[i][0] == '"' && *get_last_char(strv[i]) != '"')
		{
			char c = ' ';
			while (c != '\0')
			{
				c = getchar();
				*(get_last_char(strv[i]) + 1) = c;
				if (c == '"')
				{
					break;
				}
			}
		}
		i += symbol_split(strv, i);
		if (is_strv_complete(strv, i + 1))
		{
			break;
		}
		++i;
	}
	fclose(file);
	return strv;
}

/* Read the contents from the buffer and convert them to a parser-friendly strv. */
char **read_buf()
{
	char **strv = construct_strv();
	int i = 0;
	while (i < STRV_SIZE)
	{
		char *s = malloc(STR_SIZE * sizeof(char));
		scanf("%s", s);
		strcpy(strv[i], s);
		free(s);
		if (strv[i][0] == '"' && *get_last_char(strv[i]) != '"')
		{
			char c = ' ';
			while (c != '\0')
			{
				c = getchar();
				char *s = malloc(STR_SIZE * sizeof(char));
				s[0] = c;
				s[1] = '\0';
				strcat(strv[i], s);
				free(s);
				if (c == '"')
				{
					break;
				}
			}
			printf("\n");
		}
		i += symbol_split(strv, i);
		if (is_strv_complete(strv, i + 1))
		{
			print_strv(strv);
			break;
		}
		++i;
	}
	return strv;
}

/* Split the strv into parser-friendly strv. */
int symbol_split(char **strv, int i)
{
	int count = 0;
	char c = strv[i][0];
	c = *get_last_char(strv[i]);
	if (strcmp(strv[i], ".") == 0)
	{
		return count;
	}
	while (c == '.')
	{
		++count;
		*get_last_char(strv[i]) = '\0';
		char *str = malloc(STR_SIZE * sizeof(char));
		str[0] = c;
		str[1] = '\0';
		strv_insert(strv, str, i + 1);
		free(str);
		c = *get_last_char(strv[i]);
	}
	return count;
}