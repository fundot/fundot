#ifndef __STR_PAIR_H__
#define __STR_PAIR_H__

typedef struct str_pair
{
	char *first;
	char *second;
} str_pair;

str_pair *construct_str_pair(char *first, char *second);
void destroy_str_pair(str_pair *sp);

#endif