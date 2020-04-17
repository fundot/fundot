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
		if (strv[i][0] == '"' && !(*last_char(strv[i]) == '"' && last_char(strv[i]) != &strv[i][0]))
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
		if (strv[i][0] == '"' && !(*last_char(strv[i]) == '"' && last_char(strv[i]) != &strv[i][0]))
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
		}
		i += symbol_split(strv, i);
		if (is_strv_complete(strv, i + 1))
		{
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
	c = *last_char(strv[i]);
	if (c == '}' || c == ']')
	{
		*last_char(strv[i]) = '.';
		c = '.';
	}
	if (strcmp(strv[i], "{") == 0)
	{
		strcpy(strv[i], "Block");
		return count;
	}
	else if (strcmp(strv[i], "[") == 0)
	{
		strcpy(strv[i], "List");
		return count;
	}
	if (strcmp(strv[i], ".") == 0)
	{
		return count;
	}
	while (c == '.')
	{
		if (last_char(strv[i]) == &strv[i][0])
		{
			break;
		}
		++count;
		*last_char(strv[i]) = '\0';
		char *str = malloc(STR_SIZE * sizeof(char));
		str[0] = c;
		str[1] = '\0';
		strv_insert(strv, str, i + 1);
		free(str);
		c = *last_char(strv[i]);
		if (c == '}' || c == ']')
		{
			*last_char(strv[i]) = '.';
			c = '.';
		}
	}
	c = strv[i][0];
	while (c == '[' || c == '{')
	{
		if (strv[i][1] == '\0')
		{
			break;
		}
		++count;
		char *str = malloc(STR_SIZE * sizeof(char));
		strcpy(str, strv[i] + 1);
		strv_insert(strv, str, i + 1);
		if (c == '[')
		{
			strcpy(strv[i], "List");
		}
		else if (c == '{')
		{
			strcpy(strv[i], "Block");
		}
		strv[i][1] = '\0';
		free(str);
		c = strv[++i][0];
	}
	return count;
}