#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"
#include "fun.h"
#include "macro.h"
#include "debug.h"

fun *construct_fun(char **strv)
{
	fun *f = malloc(sizeof(fun));
	f->name = malloc(STR_SIZE * sizeof(char));
	int i = 1;
	strcpy(f->name, strv[i++]);
	f->argv = malloc(MAX_ARGC * sizeof(char *));
	while (i < MAX_ARGC + 1)
	{
		f->argv[i - 2] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->argv[i - 2], strv[i]);
		if (strcmp(strv[i + 1], "\"") == 0)
		{
			break;
		}
		++i;
	}
	f->argc = i - 1;
	i += 2;
	f->body = malloc(MAX_FUN_BODY_SIZE * sizeof(char *));
	int start_word_count = 0, end_word_count = 0, j = 0;
	while (j < MAX_FUN_BODY_SIZE)
	{
		if (strcmp("\"", strv[i]) == 0)
		{
			++i;
			continue;
		}
		if (str_info(strv[i]) == 0)
		{
			++start_word_count;
		}
		else if (str_info(strv[i]) == 1)
		{
			++end_word_count;
			if (start_word_count == end_word_count - 1)
			{
				break;
			}
		}
		f->body[j] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->body[j], strv[i]);
		++i;
		++j;
	}
	f->bodyc = j;
	return f;
}

void destroy_fun(fun *f)
{
	free(f->name);
	for (int i = 0; i < MAX_ARGC; ++i)
	{
		free(f->argv[i]);
	}
	free(f->argv);
	for (int i = 0; i < MAX_FUN_BODY_SIZE; ++i)
	{
		free(f->body[i]);
	}
	free(f->body);
	free(f);
}