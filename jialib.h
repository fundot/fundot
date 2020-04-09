#ifndef __JIALIB_H__
#define __JIALIB_H__

#include "fun_map.h"

extern fun_map *global_fun_map;

int int_hash(int sz, int i);
int str_hash(int sz, char *s);
char **get_first_expr(char **strv);
void delete_all_quotation_marks(char **strv);

char **eval(char **strv);

#endif