#ifndef __JIALIB_H__
#define __JIALIB_H__

#include "fun_map.h"

extern fun_map *global_fun_map;

int int_hash(int sz, int i);
int str_hash(int sz, char *s);

char **eval(char **strv);

#endif