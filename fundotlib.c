#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "fundotio.h"
#include "fundotlib.h"
#include "str.h"
#include "strv.h"
#include "str_map.h"
#include "fun.h"
#include "fun_map.h"
#include "macro.h"
#include "debug.h"

int int_hash(int sz, int i)
{
	return i % sz;
}

int str_hash(int sz, char *s)
{
	unsigned long hash = 5381;
	int c = 0;
	for (int i = 0; s[i] != '\0'; ++i)
	{
		c = s[i];
		hash = ((hash << 5) + hash) + c;
	}
	return hash % sz;
}

char **get_first_expr(char **strv)
{
	char **new_strv = construct_strv();
	int start_word_count = 0, end_word_count = 0, i = 0;
	while (start_word_count != end_word_count || start_word_count == 0)
	{
		if (str_info(strv[i]) == 0)
		{
			++start_word_count;
		}
		else if (strcmp(strv[i], ".") == 0)
		{
			++end_word_count;
		}
		strcpy(new_strv[i], strv[i]);
		++i;
	}
	return new_strv;
}

void delete_all_quotation_marks(char **strv)
{
	int start_word_count = 0, end_word_count = 0, i = 0;
	while (start_word_count != end_word_count || start_word_count == 0)
	{
		if (str_info(strv[i]) == 0)
		{
			++start_word_count;
		}
		else if (strcmp(strv[i], ".") == 0)
		{
			++end_word_count;
		}
		if (strcmp(strv[i], "\"") == 0)
		{
			strv_delete(strv, i);
			continue;
		}
		++i;
	}
}

char **number_to_string(double num)
{
	char **strv = construct_strv();
	if (num - (int)num < EPSILON)
	{
		sprintf(strv[0], "%d", (int)num);
	}
	else
	{
		sprintf(strv[0], "%f", num);
	}
	return strv;
}

char **eval(char **strv)
{
	char **new_strv = construct_strv();
	if (strcmp(strv[0], "If") == 0)
	{
		strcpy(strv[0], "Cond");
	}
	if (strcmp(strv[0], "Exit") == 0 || strcmp(strv[0], "Quit") == 0)
	{
		exit(0);
	}
	if (strcmp(strv[0], "Quote") == 0)
	{
		int start_word_count = 0, end_word_count = 0, i = 1, j = 0;
		while (start_word_count != end_word_count - 1)
		{
			if (str_info(strv[i]) == 0)
			{
				++start_word_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_word_count;
			}
			if (start_word_count == end_word_count - 1)
			{
				break;
			}
			strcpy(new_strv[j++], strv[i++]);
		}
		return new_strv;
	}
	else if (strcmp(strv[0], "Def") == 0)
	{
		fun_map_insert(global_fun_map, construct_fun(strv + 1));
		strcpy(new_strv[0], "defined");
		return new_strv;
	}
	else if (strcmp(strv[0], "Set") == 0)
	{
		char **nsv = eval(get_first_expr(strv + 2));
		strv_insert_strv(nsv, strv, 0);
		fun_map_insert(global_fun_map, construct_fun(nsv));
		destroy_strv(nsv);
		strcpy(new_strv[0], "set");
		return new_strv;
	}
	else if (strcmp(strv[0], "Cond") == 0)
	{
		int start_word_count = 0, end_word_count = 0, i = 1, j = 0;
		while (start_word_count != end_word_count - 1)
		{
			strcpy(new_strv[j++], strv[i]);
			if (strcmp(new_strv[j - 1], "else") == 0)
			{
				strcpy(new_strv[j - 1], "true");
			}
			if (str_info(strv[i]) == 0)
			{
				++start_word_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_word_count;
			}
			if (start_word_count == end_word_count)
			{
				char **nsv = eval(new_strv);
				if (strcmp(nsv[0], "true") == 0)
				{
					new_strv = eval(get_first_expr(strv + i + 1));
					return new_strv;
				}
				destroy_strv(nsv);
				j = 0;
			}
			++i;
		}
	}
	if (str_info(strv[0]) == 0 && second_upper_index_outside_quote(strv) != -1)
	{
		int start_word_count = 0, end_word_count = 0, i = 0, strc = 0;
		while (start_word_count > end_word_count || start_word_count == 0)
		{
			int stri = str_info(strv[i]);
			if (stri == 0)
			{
				++start_word_count;
				if (start_word_count != 1)
				{
					int swc = 0, ewc = 0, j = 0;
					char **sv = construct_strv();
					while (swc > ewc || swc == 0)
					{
						int si = str_info(strv[i]);
						if (si == 0)
						{
							++swc;
						}
						else if (si == 1)
						{
							ewc += end_dot_count(strv[i]);
							if (swc <= ewc)
							{
								++end_word_count;
							}
						}
						strcpy(sv[j++], strv[i++]);
					}
					--i;
					char **nsv = eval(sv);
					strv_delete(new_strv, strc);
					strc += strv_insert_strv(new_strv, nsv, strc);
					destroy_strv(nsv);
					destroy_strv(sv);
				}
				else
				{
					strcpy(new_strv[strc++], strv[i]);
					++i;
					continue;
				}
			}
			else if (stri == 1)
			{
				strcpy(new_strv[strc++], strv[i]);
				++end_word_count;
			}
			else
			{
				strcpy(new_strv[strc++], strv[i]);
			}
			++i;
		}
		if (str_info(new_strv[strc - 1]) != 1)
		{
			new_strv[strc] = malloc(sizeof(char *));
			new_strv[strc][0] = '.';
			new_strv[strc][1] = '\0';
		}
		return eval(new_strv);
	}
	int start_word_count = 0, end_word_count = 0, i = 0;
	while (start_word_count > end_word_count || start_word_count == 0)
	{
		int stri = str_info(strv[i]);
		if (stri == 0)
		{
			++start_word_count;
		}
		else if (stri == 1)
		{
			++end_word_count;
		}
		else if (i == 0)
		{
			break;
		}
		if (global_fun_map->funs[str_hash(global_fun_map->size, strv[i])].name != NULL)
		{
			fun *f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[i])];
			if (f->argc > 0)
			{
				str_map *sm = construct_str_map(STR_MAP_SIZE);
				for (int j = 0; j < f->argc; ++j)
				{
					if (str_info(strv[i + 1]) == 0 && second_upper_index_outside_quote(strv + i + 1) != -1)
					{
					}
					str_pair *sp = construct_str_pair(f->argv[j], strv[i + 1]);
					strv_delete(strv, i + 1);
					str_map_insert(sm, sp);
					destroy_str_pair(sp);
				}
				strv_delete(strv, i);
				strv_delete(strv, i);
				char **nsv = construct_strv();
				for (int j = f->bodyc - 1; j >= 0; --j)
				{
					if (sm->strs[str_hash(sm->size, f->body[j])][0] != '\0')
					{
						strv_insert(nsv, sm->strs[str_hash(sm->size, f->body[j])], i);
						continue;
					}
					strv_insert(nsv, f->body[j], i);
				}
				strv_insert_strv(strv, eval(nsv), i);
				if (i == 0)
				{
					strcpy(new_strv[0], strv[0]);
					return new_strv;
				}
				destroy_strv(nsv);
				destroy_str_map(sm);
			}
		}
		++i;
	}
	start_word_count = 0, end_word_count = 0, i = 0;
	while (start_word_count > end_word_count || start_word_count == 0)
	{
		int stri = str_info(strv[i]);
		if (stri == 0)
		{
			++start_word_count;
		}
		else if (stri == 1)
		{
			++end_word_count;
		}
		else if (i == 0)
		{
			break;
		}
		if (global_fun_map->funs[str_hash(global_fun_map->size, strv[i])].name != NULL)
		{
			fun *f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[i])];
			if (f->argc == 0)
			{
				char **nsv = eval(f->body);
				strv_delete(strv, i);
				i += strv_insert_strv(strv, nsv, i) - 1;
				destroy_strv(nsv);
			}
		}
		++i;
	}
	if (strcmp(strv[0], "Import") == 0)
	{
		return eval(read_file(strv[1]));
	}
	if (strcmp(strv[0], "Eval") == 0)
	{
		char **nsv = construct_strv();
		int start_word_count = 0, end_word_count = 0, i = 1, j = 0;
		while (start_word_count != end_word_count - 1)
		{
			if (str_info(strv[i]) == 0)
			{
				++start_word_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_word_count;
			}
			if (start_word_count == end_word_count - 1)
			{
				break;
			}
			strcpy(nsv[j++], strv[i++]);
		}
		strv_cpy(new_strv, eval(nsv));
		destroy_strv(nsv);
		return new_strv;
	}
	else if (strcmp(strv[0], "Block") == 0)
	{
		for (int i = 0; i < STRV_SIZE; ++i)
		{
			if (strcmp(strv[i + 1], ".") == 0)
			{
				strcpy(new_strv[0], strv[i]);
				return new_strv;
			}
		}
	}
	else if (strcmp(strv[0], "Equal") == 0)
	{
		if (strcmp(strv[1], strv[2]) == 0)
		{
			strcpy(new_strv[0], "true");
		}
		else
		{
			strcpy(new_strv[0], "false");
		}
		return new_strv;
	}
	else if (strcmp(strv[0], "CAR") == 0 || strcmp(strv[0], "First") == 0)
	{
		if (isupper(strv[1][0]))
		{
			destroy_strv(new_strv);
			return get_first_expr(strv + 1);
		}
		strcpy(new_strv[0], strv[1]);
		return new_strv;
	}
	else if (strcmp(strv[0], "CDR") == 0 || strcmp(strv[0], "Rest") == 0)
	{
		int i = 1;
		if (isupper(strv[1][0]))
		{
			int swc = 0, ewc = 0;
			while (swc != ewc || swc == 0)
			{
				if (isupper(strv[i][0]))
				{
					++swc;
				}
				else if (strcmp(strv[i], ".") == 0)
				{
					++ewc;
				}
				++i;
			}
			--i;
		}
		int strc = 0;
		strv_cpy(new_strv, strv + i + 1);
		while (strcmp(new_strv[strc++], "null") != 0)
		{
		}
		strcpy(new_strv[strc - 2], "null");
		return new_strv;
	}
	else if (strcmp(strv[0], "Print") == 0)
	{
		printf("%s\n", strv[1]);
		strcpy(new_strv[0], "null");
		return new_strv;
	}
	else if (strcmp(strv[0], "Add") == 0)
	{
		double first = 0.0, second = 0.0;
		sscanf(strv[1], "%lf", &first);
		sscanf(strv[2], "%lf", &second);
		new_strv = number_to_string(first + second);
		return new_strv;
	}
	else if (strcmp(strv[0], "Sub") == 0)
	{
		double first = 0.0, second = 0.0;
		sscanf(strv[1], "%lf", &first);
		sscanf(strv[2], "%lf", &second);
		new_strv = number_to_string(first - second);
		return new_strv;
	}
	else if (strcmp(strv[0], "Mul") == 0)
	{
		double first = 0.0, second = 0.0;
		sscanf(strv[1], "%lf", &first);
		sscanf(strv[2], "%lf", &second);
		new_strv = number_to_string(first * second);
		return new_strv;
	}
	else if (strcmp(strv[0], "Div") == 0)
	{
		double first = 0.0, second = 0.0;
		sscanf(strv[1], "%lf", &first);
		sscanf(strv[2], "%lf", &second);
		new_strv = number_to_string(first / second);
		return new_strv;
	}
	else if (strcmp(strv[0], "Mod") == 0)
	{
		int first = 0, second = 0;
		sscanf(strv[1], "%d", &first);
		sscanf(strv[2], "%d", &second);
		new_strv = number_to_string(first % second);
		return new_strv;
	}
	else if (global_fun_map->funs[str_hash(global_fun_map->size, strv[0])].name != NULL)
	{
		fun *f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[0])];
		if (f->argc == 0)
		{
			char **nsv = eval(f->body);
			strv_delete(strv, 0);
			strv_insert_strv(strv, nsv, 0);
			destroy_strv(nsv);
			strv_insert_strv(new_strv, strv, 0);
			return new_strv;
		}
	}
	else
	{
		strv_insert_strv(new_strv, strv, 0);
		new_strv[0][0] = tolower(new_strv[0][0]);
		return new_strv;
	}
	strcpy(new_strv[0], "null");
	return new_strv;
}