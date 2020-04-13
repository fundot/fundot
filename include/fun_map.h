#ifndef __FUN_MAP_H__
#define __FUN_MAP_H__

#include "fun.h"

typedef struct fun_map
{
	fun *funs;
	int size;
} fun_map;

fun_map *construct_fun_map(int sz);
void destroy_fun_map(fun_map *fm);
int fun_map_insert(fun_map *fm, fun *f);

#endif