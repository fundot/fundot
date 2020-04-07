#ifndef __STR_MAP_H__
#define __STR_MAP_H__

#include "str_pair.h"

typedef struct str_map
{
	char **strs;
	int size;
} str_map;

str_map *construct_str_map(int sz);
void destroy_str_map(str_map *sm);
int str_map_insert(str_map *sm, str_pair *sp);

#endif