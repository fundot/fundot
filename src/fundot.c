#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fundotio.h"
#include "fundotlib.h"
#include "str.h"
#include "strv.h"
#include "str_pair.h"
#include "str_map.h"
#include "fun.h"
#include "fun_map.h"
#include "macro.h"
#include "debug.h"

fun_map *global_fun_map;

int main(int argc, char **argv)
{
	/* Construct a global fun map for use later. */
	global_fun_map = construct_fun_map(FUN_MAP_SIZE);
	printf("Fun.\n");
	/* If we want to eval a file directly */
	if (argc == 2)
	{
		char **strv = read_file(argv[1]);
		char **new_strv = eval(strv);
		if (strcmp(new_strv[0], " ") != 0)
		{
			print_strv(new_strv);
		}
		destroy_strv(strv);
		destroy_strv(new_strv);
	}
	else /* If we want to open the parser. */
	{
		for (;;)
		{
			printf(">>> ");
			char **strv = read_buf();
			char **new_strv = eval(strv);
			if (strcmp(new_strv[0], "null") != 0)
			{
				print_strv(new_strv);
			}
			destroy_strv(strv);
			destroy_strv(new_strv);
		}
	}
	destroy_fun_map(global_fun_map);
	return 0;
}