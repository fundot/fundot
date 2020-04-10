#include <stdlib.h>
#include "fundotlib.h"
#include "fun_map.h"

fun_map *construct_fun_map(int sz)
{
	fun_map *fm = malloc(sizeof(fun_map));
	fm->size = sz;
	fm->funs = malloc(fm->size * sizeof(fun));
	return fm;
}

void destroy_fun_map(fun_map *fm)
{
	free(fm->funs);
	free(fm);
}

int fun_map_insert(fun_map *fm, fun *f)
{
	int i = str_hash(fm->size, f->name);
	fm->funs[i] = *f;
	return i;
}