#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "strv.h"
#include "jiaio.h"
#include "macro.h"
#include "debug.h"

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
		i += symbol_split(strv, i);
		if (is_strv_complete(strv, i + 1))
		{
			break;
		}
		++i;
	}
	return strv;
}

int symbol_split(char **strv, int i)
{
	int count = 0;
	char c = strv[i][0];
	if (c == '"')
	{
		strcpy(strv[i + 1], strv[i] + 1);
		strv[i][1] = '\0';
		++count;
		++i;
	}
	c = *get_last_char(strv[i]);
	while (c == '.' || c == ':' || c == '"')
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