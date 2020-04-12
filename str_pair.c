#include <string.h>
#include <stdlib.h>
#include "str_pair.h"
#include "macro.h"

/* Constructor of str_pair. */
str_pair *construct_str_pair(char *first, char *second)
{
	str_pair *sp = malloc(sizeof(str_pair));
	sp->first = malloc(STR_SIZE * sizeof(char));
	strcpy(sp->first, first);
	sp->second = malloc(STR_SIZE * sizeof(char));
	strcpy(sp->second, second);
	return sp;
}

/* Destroyer of str_pair. */
void destroy_str_pair(str_pair *sp)
{
	free(sp->first);
	free(sp->second);
	free(sp);
}