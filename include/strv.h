#ifndef __STRV_H__
#define __STRV_H__

#include "str.h"

char **construct_strv();
void destroy_strv(char **strv);
void clear_strv(char **strv);
void strv_insert(char **strv, char *str, int i);
void strv_delete(char **strv, int i);
int strv_count(char **strv);
int is_strv_complete(char **strv, int p);
void print_strv(char **strv);
void strv_cpy(char **strv1, char **strv2);
int strv_insert_strv(char **strv1, char **strv2, int i);
int last_str_index(char **strv);
int first_upper_index(char **strv);
int second_upper_index_outside_quote(char **strv);
int second_upper_index_outside_list(char **strv);

#endif