#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "str.h"
#include "strv.h"
#include "fun.h"
#include "macro.h"
#include "debug.h"

/* Constructor for fun. */
fun *construct_fun(char **strv)
{
	fun *f = malloc(sizeof(fun));
	f->name = malloc(STR_SIZE * sizeof(char));
	int i = 0;
	strcpy(f->name, strv[i++]);
	if (isupper(f->name[0]) == 0)
	{
		f->argc = 0;
		f->body = malloc(MAX_FUN_BODY_SIZE * sizeof(char *));
		while (strcmp(strv[i], "null") != 0)
		{
			f->body[i - 1] = malloc(STR_SIZE * sizeof(char));
			strcpy(f->body[i - 1], strv[i]);
			++i;
		}
		f->bodyc = i - 2;
		strcpy(f->body[i - 2], "null");
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
	int j = 0;
	while (strcmp(strv[i], "null") != 0)
	{
		f->body[j] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->body[j], strv[i]);
		++i;
		++j;
	}
	f->body[j] = malloc(STR_SIZE * sizeof(char));
	strcpy(f->body[j], "null");
	f->bodyc = j;
	return f;
}

/* Destroyer for fun */
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