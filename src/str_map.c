#include <stdlib.h>
#include <string.h>
#include "fundotlib.h"
#include "str_pair.h"
#include "str_map.h"
#include "macro.h"

/* Constructor of str_map. */
str_map *construct_str_map(int sz)
{
	str_map *sm = malloc(sizeof(str_map));
	sm->size = sz;
	sm->strs = malloc(sm->size * sizeof(char *));
	for (int i = 0; i < sm->size; ++i)
	{
		sm->strs[i] = malloc(STR_SIZE * sizeof(char));
		sm->strs[i][0] = '\0';
	}
	return sm;
}

/* Destroyer of str_map. */
void destroy_str_map(str_map *sm)
{
	for (int i = 0; i < sm->size; ++i)
	{
		free(sm->strs[i]);
	}
	free(sm);
}

/* Insert a str_pair sp to the str_map sm. */
int str_map_insert(str_map *sm, str_pair *sp)
{
	int i = str_hash(sm->size, sp->first);
	strcpy(sm->strs[i], sp->second);
	return i;
}