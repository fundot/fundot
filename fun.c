#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "str.h"
#include "fun.h"
#include "macro.h"
#include "debug.h"

fun *construct_fun(char **strv)
{
	fun *f = malloc(sizeof(fun));
	f->name = malloc(STR_SIZE * sizeof(char));
	int i = 0;
	strcpy(f->name, strv[i++]);
	if (isupper(f->name[0]) == 0)
	{
		f->argc = 0;
		f->bodyc = 1;
		f->body = malloc(MAX_FUN_BODY_SIZE * sizeof(char *));
		f->body[0] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->body[0], strv[i]);
		return f;
	}
	f->argv = malloc(MAX_ARGC * sizeof(char *));
	while (i < MAX_ARGC + 1)
	{
		if (strcmp(strv[i], ".") == 0)
		{
			break;
		}
		f->argv[i - 1] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->argv[i - 1], strv[i]);
		++i;
	}
	f->argc = i - 1;
	++i;
	f->body = malloc(MAX_FUN_BODY_SIZE * sizeof(char *));
	int start_word_count = 0, end_word_count = 0, j = 0;
	while (j < MAX_FUN_BODY_SIZE)
	{
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