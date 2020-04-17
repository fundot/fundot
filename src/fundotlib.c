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

/* Return the hash value of int i under the size s. */
int int_hash(int sz, int i)
{
	return i % sz;
}

/* Return the hash value of str s under the size s. */
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

/* Return the pointer to the first expression of strv. */
char **first_expr(char **strv)
{
	char **new_strv = construct_strv();
	if (isupper(strv[0][0]) == 0)
	{
		strcpy(new_strv[0], strv[0]);
		return new_strv;
	}
	int start_count = 0, end_count = 0, i = 0;
	while (start_count != end_count || start_count == 0)
	{
		if (isupper(strv[i][0]))
		{
			++start_count;
		}
		else if (strcmp(strv[i], ".") == 0)
		{
			++end_count;
		}
		strcpy(new_strv[i], strv[i]);
		++i;
	}
	return new_strv;
}

/* Delete all quotation marks of strv. */
void delete_all_quotation_marks(char **strv)
{
	int start_count = 0, end_count = 0, i = 0;
	while (start_count != end_count || start_count == 0)
	{
		if (isupper(strv[i][0]))
		{
			++start_count;
		}
		else if (strcmp(strv[i], ".") == 0)
		{
			++end_count;
		}
		if (strcmp(strv[i], "\"") == 0)
		{
			strv_delete(strv, i);
			continue;
		}
		++i;
	}
}

/* Change the number to string. */
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
	strcpy(strv[1], "null");
	return strv;
}

/* Evaluate the strv. */
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
		int start_count = 0, end_count = 0, i = 1, j = 0;
		while (start_count != end_count - 1)
		{
			if (isupper(strv[i][0]))
			{
				++start_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_count;
			}
			if (start_count == end_count - 1)
			{
				break;
			}
			strcpy(new_strv[j++], strv[i++]);
		}
		strv_insert(new_strv, "List", 0);
		strv_insert(new_strv, ".", last_str_index(new_strv) + 1);
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
		char **nsv = eval(first_expr(strv + 2));
		strv_insert(nsv, strv[1], 0);
		strv_insert(nsv, ".", last_str_index(nsv) + 1);
		fun_map_insert(global_fun_map, construct_fun(nsv));
		destroy_strv(nsv);
		strcpy(new_strv[0], "set");
		return new_strv;
	}
	else if (strcmp(strv[0], "Cond") == 0)
	{
		int start_count = 0, end_count = 0, i = 1, j = 0;
		while (start_count != end_count - 1)
		{
			strcpy(new_strv[j++], strv[i]);
			if (strcmp(new_strv[j - 1], "else") == 0)
			{
				strcpy(new_strv[j - 1], "true");
			}
			if (isupper(strv[i][0]))
			{
				++start_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_count;
			}
			if (start_count == end_count)
			{
				char **nsv = eval(new_strv);
				if (strcmp(nsv[0], "true") == 0)
				{
					new_strv = eval(first_expr(strv + i + 1));
					return new_strv;
				}
				destroy_strv(nsv);
				j = 0;
			}
			++i;
		}
	}
	else if (strcmp(strv[0], "While") == 0)
	{
		char **pred = eval(first_expr(strv + 1));
		while (strcmp(pred[0], "true") == 0)
		{
			int i = strv_count(first_expr(strv + 1));
			clear_strv(pred);
			eval(first_expr(strv + 1 + i));
			pred = eval(first_expr(strv + 1));
		}
		destroy_strv(pred);
		strcpy(new_strv[0], "null");
		return new_strv;
	}
	int start_count = 0, end_count = 0, i = 0;
	while (isupper(strv[0][0]) && second_upper_index_outside_list(strv) != -1 && second_upper_index_outside_quote(strv) != -1)
	{
		int start_count = 0, end_count = 0, i = 0;
		while (start_count > end_count || start_count == 0)
		{
			if (isupper(strv[i][0]))
			{
				++start_count;
				if (i != 0)
				{
					char **sv = first_expr(strv + i);
					for (int j = 0; j < strv_count(sv); ++j)
					{
						strv_delete(strv, i);
					}
					char **nsv = eval(sv);
					strv_insert_strv(strv, nsv, i);
					i += strv_count(nsv) - 1;
					destroy_strv(nsv);
					destroy_strv(sv);
					++end_count;
				}
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_count;
			}
			else
			{
				char **sv = construct_strv();
				strcpy(sv[0], strv[i]);
				strv_delete(strv, i);
				char **nsv = eval(sv);
				strv_insert_strv(strv, nsv, i);
				i += strv_count(nsv) - 1;
				destroy_strv(nsv);
				destroy_strv(sv);
			}
			++i;
		}
	}
	while (start_count > end_count || start_count == 0)
	{
		if (global_fun_map->funs[str_hash(global_fun_map->size, strv[i])].name != NULL)
		{
			fun_map *local_fun_map = construct_fun_map(FUN_MAP_SIZE);
			fun *f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[i])];
			for (int j = 0; j < f->argc; ++j)
			{
				char **nsv = first_expr(strv + i + 1);
				for (int k = 0; k < strv_count(nsv); ++k)
				{
					strv_delete(strv, i + 1);
				}
				strv_insert(nsv, f->argv[j], 0);
				strv_insert(nsv, ".", last_str_index(nsv) + 1);
				fun_map_insert(local_fun_map, construct_fun(nsv));
				destroy_strv(nsv);
			}
			if (isupper(strv[i][0]))
			{
				++end_count;
				strv_delete(strv, i + 1);
			}
			strv_delete(strv, i);
			char **nsv = construct_strv();
			for (int j = f->bodyc - 1; j >= 0; --j)
			{
				if (local_fun_map->funs[str_hash(local_fun_map->size, f->body[j])].name != NULL)
				{
					strv_insert_strv(nsv, local_fun_map->funs[str_hash(local_fun_map->size, f->body[j])].body, 0);
					continue;
				}
				strv_insert(nsv, f->body[j], 0);
			}
			strv_insert_strv(strv, eval(nsv), i);
			destroy_strv(nsv);
			destroy_fun_map(local_fun_map);
		}
		if (isupper(strv[i][0]))
		{
			++start_count;
		}
		else if (strcmp(strv[i], ".") == 0)
		{
			++end_count;
		}
		else if (i == 0)
		{
			break;
		}
		++i;
	}
	if (strcmp(strv[0], "Import") == 0)
	{
		return eval(read_file(strv[1]));
	}
	if (strcmp(strv[0], "List") == 0)
	{
		strv_cpy(new_strv, strv);
		return new_strv;
	}
	if (strcmp(strv[0], "Eval") == 0)
	{
		char **nsv = construct_strv();
		int start_count = 0, end_count = 0, i = 1, j = 0;
		while (start_count != end_count - 1)
		{
			if (isupper(strv[i][0]))
			{
				++start_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_count;
			}
			if (start_count == end_count - 1)
			{
				break;
			}
			strcpy(nsv[j++], strv[i++]);
		}
		strv_cpy(new_strv, eval(nsv));
		destroy_strv(nsv);
		return new_strv;
	}
	else if (strcmp(strv[0], "Atom") == 0)
	{
		int start_count = 0, end_count = 0, i = 1, j = 0;
		while (start_count != end_count - 1)
		{
			if (isupper(strv[i][0]))
			{
				++start_count;
			}
			else if (strcmp(strv[i], ".") == 0)
			{
				++end_count;
			}
			if (start_count == end_count - 1)
			{
				break;
			}
			strcpy(new_strv[j++], strv[i++]);
		}
		int k = 0;
		while (strcmp(new_strv[k++], "null") != 0)
		{
		}
		if (strcmp(new_strv[0], "List") == 0 && strcmp(new_strv[1], ".") == 0)
		{
			strcpy(new_strv[0], "true");
			strcpy(new_strv[1], "null");
		}
		else if (k < 3)
		{
			strcpy(new_strv[0], "true");
			strcpy(new_strv[1], "null");
		}
		else
		{
			strcpy(new_strv[0], "false");
			strcpy(new_strv[1], "null");
		}
		return new_strv;
	}
	else if (strcmp(strv[0], "Block") == 0)
	{
		int i = strv_count(strv) - 2;
		if (strcmp(strv[i], ".") != 0)
		{
			strcpy(new_strv[0], strv[i]);
			return new_strv;
		}
		int sc = 0, ec = 0;
		while (sc != ec || ec == 0)
		{
			strv_insert(new_strv, strv[i], 0);
			if (strcmp(strv[i], ".") == 0)
			{
				++ec;
			}
			else if (isupper(strv[i][0]))
			{
				++sc;
			}
			--i;
		}
		return new_strv;
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
		if (isupper(strv[2][0]))
		{
			char **nsv = first_expr(strv + 2);
			strv_cpy(new_strv, nsv);
			destroy_strv(nsv);
		}
		else
		{
			strcpy(new_strv[0], strv[2]);
		}
		return new_strv;
	}
	else if (strcmp(strv[0], "CDR") == 0 || strcmp(strv[0], "Rest") == 0)
	{
		int i = 2;
		if (isupper(strv[2][0]))
		{
			int sc = 0, ec = 0;
			while (sc != ec || sc == 0)
			{
				if (isupper(strv[i][0]))
				{
					++sc;
				}
				else if (strcmp(strv[i], ".") == 0)
				{
					++ec;
				}
				++i;
			}
			--i;
		}
		strv_cpy(new_strv, strv + i + 1);
		strv_insert(new_strv, "List", 0);
		strv_delete(new_strv, last_str_index(new_strv));
		return new_strv;
	}
	else if (strcmp(strv[0], "Cons") == 0)
	{
		if (strcmp(strv[2], "List") == 0)
		{
			char **nsv = first_expr(strv + 2);
			strv_cpy(new_strv, nsv);
			destroy_strv(nsv);
			strv_insert(new_strv, strv[1], 1);
			return new_strv;
		}
		else
		{
			strcpy(new_strv[0], "List");
			strcpy(new_strv[1], strv[1]);
			strcpy(new_strv[2], strv[2]);
			strcpy(new_strv[3], ".");
			return new_strv;
		}
	}
	else if (strcmp(strv[0], "Print") == 0)
	{
		char **nsv = first_expr(strv + 1);
		print_strv(nsv);
		destroy_strv(nsv);
		strcpy(new_strv[0], "null");
		return new_strv;
	}
	else if (strcmp(strv[0], "Less") == 0)
	{
		double first = 0.0, second = 0.0;
		sscanf(strv[1], "%lf", &first);
		sscanf(strv[2], "%lf", &second);
		if (first < second)
		{
			strcpy(new_strv[0], "true");
		}
		else
		{
			strcpy(new_strv[0], "false");
		}
		return new_strv;
	}
	else if (strcmp(strv[0], "Greater") == 0)
	{
		double first = 0.0, second = 0.0;
		sscanf(strv[1], "%lf", &first);
		sscanf(strv[2], "%lf", &second);
		if (first > second)
		{
			strcpy(new_strv[0], "true");
		}
		else
		{
			strcpy(new_strv[0], "false");
		}
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