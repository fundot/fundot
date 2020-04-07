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
	int start_word_count = 0, end_word_count = 0, i = 0;
	char **strv = construct_strv();
	while (start_word_count != end_word_count || start_word_count == 0)
	{
		char *s = malloc(STR_SIZE * sizeof(char));
		fscanf(file, "%s", s);
		strcpy(strv[i++], s);
		if (str_info(s) == 0)
		{
			++start_word_count;
			if (*get_last_char(s) == '.')
			{
				++end_word_count;
			}
		}
		else if (str_info(s) == 1)
		{
			int j;
			for (j = 0; j < end_dot_count(s); ++j)
			{
				++end_word_count;
				*get_last_char(strv[i - 1]) = '\0';
				strv[i + j][0] = '.';
				strv[i + j][1] = '\0';
			}
			i += j;
			if (*get_last_char(strv[i - 2]) == '"')
			{
				*get_last_char(strv[i - 2]) = '\0';
				char *qs = "\"";
				strv_insert(strv, qs, i - 1);
				++i;
			}
		}
		else if (str_info(s) == 2)
		{
			*get_last_char(strv[i - 1]) = '\0';
			if (str_info(strv[i - 1]) == 1)
			{
				int j;
				for (j = 0; j < end_dot_count(strv[i - 1]); ++j)
				{
					++end_word_count;
					*get_last_char(strv[i - 1]) = '\0';
					strv[i + j][0] = '.';
					strv[i + j][1] = '\0';
				}
				i += j;
			}
			strv[i][0] = ':';
			strv[i][1] = '\0';
			++i;
		}
		else if (i == 1)
		{
			break;
		}
		free(s);
	}
	fclose(file);
	return strv;
}
/*
char **read_buf()
{
	int start_word_count = 0, end_word_count = 0, i = 0;
	char **strv = construct_strv();
	while (start_word_count != end_word_count || start_word_count == 0)
	{
		char *s = malloc(STR_SIZE * sizeof(char));
		scanf("%s", s);
		strcpy(strv[i++], s);
		if (strv[i - 1][0] == '"')
		{
			strcpy(strv[i], strv[i - 1] + 1);
			strv[i - 1][1] = '\0';
			++i;
			while (*get_last_char(strv[i - 1]) != '"')
			{
				scanf("%s", s);
				strcpy(strv[i++], s);
			}
			i += symbol_split(strv, i - 1) + 2;
		}
		//
		if (*get_last_char(strv[i - 1]) == '"')
		{
			*get_last_char(strv[i - 1]) = '\0';
			strv[i + 1][0] = '"';
			strv[i + 1][1] = '\0';
			++i;
			int j;
		}
		//
		if (str_info(s) == 0)
		{
			++start_word_count;
			if (*get_last_char(s) == '.')
			{
				++end_word_count;
			}
		}
		else if (str_info(s) == 1)
		{
			int j;
			for (j = 0; j < end_dot_count(s); ++j)
			{
				++end_word_count;
				*get_last_char(strv[i - 1]) = '\0';
				strv[i + j][0] = '.';
				strv[i + j][1] = '\0';
			}
			i += j;
			if (*get_last_char(strv[i - 2]) == '"')
			{
				*get_last_char(strv[i - 2]) = '\0';
				char *qs = "\"";
				strv_insert(strv, qs, i - 1);
				++i;
			}
		}
		else if (str_info(s) == 2)
		{
			*get_last_char(strv[i - 1]) = '\0';
			if (str_info(strv[i - 1]) == 1)
			{
				int j;
				for (j = 0; j < end_dot_count(strv[i - 1]); ++j)
				{
					++end_word_count;
					*get_last_char(strv[i - 1]) = '\0';
					strv[i + j][0] = '.';
					strv[i + j][1] = '\0';
				}
				i += j;
			}
			strv[i][0] = ':';
			strv[i][1] = '\0';
			++i;
		}
		else if (i == 1)
		{
			break;
		}
		free(s);
	}
	for (int i = 0; i < 20; ++i)
	{
		printf("%s ", strv[i]);
	}
	printf("\n");
	return strv;
}
*/

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