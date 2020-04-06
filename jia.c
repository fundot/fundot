#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_SIZE 64
#define STRV_SIZE 256
#define STR_MAP_SIZE 257
#define FUN_MAP_SIZE 257
#define MAX_ARGC 16
#define MAX_FUN_BODY_SIZE 65536

#define PRINTRUNNING printf("Running..\n");

int int_hash(int sz, int i);
int str_hash(int sz, char *s);
char *get_last_char(char *s);
int str_info(char *s);
int end_dot_count(char *s);

typedef struct str_pair
{
	char *first;
	char *second;
} str_pair;

str_pair *construct_str_pair(char *first, char *second);
void destroy_str_pair(str_pair *sp);

typedef struct str_map
{
	char **strs;
	int size;
} str_map;

str_map *construct_str_map(int sz);
void destroy_str_map(str_map *sm);
int str_map_insert(str_map *sm, str_pair *sp);

typedef struct fun
{
	char *name;
	int argc;
	char **argv;
	int bodyc;
	char **body;
} fun;

fun *construct_fun(char **strv);
void destroy_fun(fun *f);

typedef struct fun_map
{
	fun *funs;
	int size;
} fun_map;

fun_map *construct_fun_map(int sz);
void destroy_fun_map(fun_map *fm);
int fun_map_insert(fun_map *fm, fun *f);
int first_upper_index(char **strv);
char **construct_strv();
void destroy_strv(char **strv);
void strv_insert(char **strv, char *str, int i);
void strv_delete(char **strv, int i);
char **eval(char **strv);
char **read_file(char *file_name);
char **read_buf();

fun_map *global_fun_map;

int main(int argc, char **argv)
{
	global_fun_map = construct_fun_map(FUN_MAP_SIZE);
	printf("Jia is here to help.\n");
	if (argc == 2)
	{
		for (;;)
		{
			char **strv = read_file(argv[1]);
			char **new_strv = eval(strv);
			printf("%s\n", new_strv[0]);
			destroy_strv(strv);
			destroy_strv(new_strv);
		}
	}
	else
	{
		for (;;)
		{
			char **strv = read_buf();
			char **new_strv = eval(strv);
			printf("%s\n", new_strv[0]);
			destroy_strv(strv);
			destroy_strv(new_strv);
		}
	}
	destroy_fun_map(global_fun_map);
	return 0;
}

int int_hash(int sz, int i)
{
	return i % sz;
}

int str_hash(int sz, char *s)
{
	int sum = 0;
	for (int i = 0; s[i] != '\0'; ++i)
	{
		sum += s[i];
	}
	return int_hash(sz, sum);
}

char *get_last_char(char *s)
{
	int i = 0;
	while (s[i] != '\0')
	{
		if (s[i + 1] == '\0')
		{
			return &s[i];
		}
		++i;
	}
	return NULL;
}

int str_info(char *s)
{
	if (isupper(s[0]))
	{
		return 0;
	}
	else if (*get_last_char(s) == '.')
	{
		return 1;
	}
	else if (*get_last_char(s) == ':')
	{
		return 2;
	}
	return -1;
}

int end_dot_count(char *s)
{
	int i = 0;
	while (s[i++] != '\0')
		;
	i -= 2;
	int count = 0;
	while (i >= 0 && s[i--] == '.')
	{
		++count;
	}
	return count;
}

str_pair *construct_str_pair(char *first, char *second)
{
	str_pair *sp = malloc(sizeof(str_pair));
	sp->first = malloc(STR_SIZE * sizeof(char));
	strcpy(sp->first, first);
	sp->second = malloc(STR_SIZE * sizeof(char));
	strcpy(sp->second, second);
	return sp;
}
void destroy_str_pair(str_pair *sp)
{
	free(sp->first);
	free(sp->second);
	free(sp);
}

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

void destroy_str_map(str_map *sm)
{
	for (int i = 0; i < sm->size; ++i)
	{
		free(sm->strs[i]);
	}
	free(sm);
}

int str_map_insert(str_map *sm, str_pair *sp)
{
	int i = str_hash(sm->size, sp->first);
	strcpy(sm->strs[i], sp->second);
	return i;
}

fun *construct_fun(char **strv)
{
	fun *f = malloc(sizeof(fun));
	f->name = malloc(STR_SIZE * sizeof(char));
	int i = 0;
	strcpy(f->name, strv[i++]);
	f->argv = malloc(MAX_ARGC * sizeof(char *));
	while (i < MAX_ARGC + 1)
	{
		f->argv[i - 1] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->argv[i - 1], strv[i]);
		if (str_info(strv[i]) == 2)
		{
			break;
		}
		++i;
	}
	f->argc = i++;
	f->body = malloc(MAX_FUN_BODY_SIZE * sizeof(char *));
	int start_word_count = 0, end_word_count = 0, j = 0;
	while (j < MAX_FUN_BODY_SIZE)
	{
		if (str_info(strv[i]) == 0)
		{
			++start_word_count;
		}
		else if (str_info(strv[i]) == 1)
		{
			++end_word_count;
			if (start_word_count == end_word_count - 1)
			{
				break;
			}
		}
		f->body[j] = malloc(STR_SIZE * sizeof(char));
		strcpy(f->body[j], strv[i]);
		++i;
		++j;
	}
	f->bodyc = j;
	return f;
}

void destroy_fun(fun *f)
{
	free(f->name);
	for (int i = 0; i < MAX_ARGC; ++i)
	{
		free(f->argv[i]);
	}
	free(f->argv);
	for (int i = 0; i < MAX_FUN_BODY_SIZE; ++i)
	{
		free(f->body[i]);
	}
	free(f->body);
	free(f);
}

fun_map *construct_fun_map(int sz)
{
	fun_map *fm = malloc(sizeof(fun_map));
	fm->size = sz;
	fm->funs = malloc(fm->size * sizeof(fun));
	return fm;
}

void destroy_fun_map(fun_map *fm)
{
	free(fm->funs);
	free(fm);
}

int fun_map_insert(fun_map *fm, fun *f)
{
	int i = str_hash(fm->size, f->name);
	fm->funs[i] = *f;
	return i;
}

int first_upper_index(char **strv)
{
	int i = 0;
	while (*get_last_char(strv[i]) != '.')
	{
		if (str_info(strv[i]) == 0)
		{
			return i;
		}
		++i;
	}
	return -1;
}

char **construct_strv()
{
	char **strv = malloc(STRV_SIZE * sizeof(char *));
	for (int i = 0; i < STRV_SIZE; ++i)
	{
		strv[i] = malloc(STR_SIZE * sizeof(char));
	}
	return strv;
}

void destroy_strv(char **strv)
{
	for (int i = 0; i < STRV_SIZE; ++i)
	{
		free(strv[i]);
	}
	free(strv);
}

void strv_insert(char **strv, char *str, int i)
{
	for (int j = STRV_SIZE - 1; j > i; --j)
	{
		strcpy(strv[j], strv[j - 1]);
	}
	strcpy(strv[i], str);
}

void strv_delete(char **strv, int i)
{
	for (int j = i; j < STRV_SIZE - 1; ++j)
	{
		strcpy(strv[j], strv[j + 1]);
	}
}

char **eval(char **strv)
{
	char **new_strv = construct_strv();
	if (strcmp(strv[0], "Def") == 0)
	{
		fun_map_insert(global_fun_map, construct_fun(strv + 1));
		strcpy(new_strv[0], strv[1]);
		return new_strv;
	}
	if (strcmp(strv[0], "Exit.") == 0)
	{
		exit(0);
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
			if (f->argc == 1)
			{
				for (int j = 0; j < f->bodyc; ++j)
				{
					strcpy(strv[i], f->body[j]);
				}
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
			if (f->argc > 1)
			{
				str_map *sm = construct_str_map(STR_MAP_SIZE);
				for (int j = 0; j < f->argc - 1; ++j)
				{
					str_pair *sp = construct_str_pair(f->argv[j], strv[i + 1]);
					strv_delete(strv, i + 1);
					str_map_insert(sm, sp);
					destroy_str_pair(sp);
				}
				strv_delete(strv, i);
				for (int j = f->bodyc - 1; j >= 0; --j)
				{
					if (sm->strs[str_hash(sm->size, f->body[j])][0] != '\0')
					{
						strv_insert(strv, sm->strs[str_hash(sm->size, f->body[j])], i);
						continue;
					}
					strv_insert(strv, f->body[j], i);
				}
				destroy_str_map(sm);
			}
		}
		++i;
	}
	if (str_info(strv[0]) == 0 && first_upper_index(strv + 1) != -1)
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
					strcpy(new_strv[strc++], eval(sv)[0]);
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
	else if (strcmp(strv[0], "Add") == 0)
	{
		int first = strv[1][0], second = strv[2][0];
		new_strv[0][0] = first + second - '0';
		new_strv[0][1] = '\0';
		return new_strv;
	}
	else if (global_fun_map->funs[str_hash(global_fun_map->size, strv[0])].name != NULL)
	{
		fun *f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[0])];
		if (f->argc == 1 && f->bodyc == 1)
		{
			free(new_strv);
			return f->body;
		}
	}
	else
	{
		free(new_strv);
		return strv;
	}
	return NULL;
}

char **read_file(char *file_name)
{
	FILE *file = fopen(file_name, "r");
	int start_word_count = 0, end_word_count = 0, i = 0;
	char **strv = construct_strv();
	while (start_word_count != end_word_count || start_word_count == 0)
	{
		char *s = malloc(STR_SIZE * sizeof(char));
		fscanf(file, "%s", s);
		strcpy(strv[i++], s);
		if (str_info(s) == 0)
		{
			++start_word_count;
			if (*get_last_char(s) == '.')
			{
				++end_word_count;
			}
		}
		else if (str_info(s) == 1)
		{
			int j;
			for (j = 0; j < end_dot_count(s); ++j)
			{
				++end_word_count;
				*get_last_char(strv[i - 1]) = '\0';
				strv[i + j][0] = '.';
				strv[i + j][1] = '\0';
			}
			i += j;
		}
		else if (str_info(s) == 2)
		{
			*get_last_char(strv[i - 1]) = '\0';
			if (str_info(strv[i - 1]) == 1)
			{
				int j;
				for (j = 0; j < end_dot_count(strv[i - 1]); ++j)
				{
					++end_word_count;
					*get_last_char(strv[i - 1]) = '\0';
					strv[i + j][0] = '.';
					strv[i + j][1] = '\0';
				}
				i += j;
			}
			strv[i][0] = ':';
			strv[i][1] = '\0';
			++i;
		}
		else if (i == 1)
		{
			break;
		}
		free(s);
	}
	return strv;
}

char **read_buf()
{
	int start_word_count = 0, end_word_count = 0, i = 0;
	char **strv = construct_strv();
	while (start_word_count != end_word_count || start_word_count == 0)
	{
		char *s = malloc(STR_SIZE * sizeof(char));
		scanf("%s", s);
		strcpy(strv[i++], s);
		if (str_info(s) == 0)
		{
			++start_word_count;
			if (*get_last_char(s) == '.')
			{
				++end_word_count;
			}
		}
		else if (str_info(s) == 1)
		{
			int j;
			for (j = 0; j < end_dot_count(s); ++j)
			{
				++end_word_count;
				*get_last_char(strv[i - 1]) = '\0';
				strv[i + j][0] = '.';
				strv[i + j][1] = '\0';
			}
			i += j;
		}
		else if (str_info(s) == 2)
		{
			*get_last_char(strv[i - 1]) = '\0';
			if (str_info(strv[i - 1]) == 1)
			{
				int j;
				for (j = 0; j < end_dot_count(strv[i - 1]); ++j)
				{
					++end_word_count;
					*get_last_char(strv[i - 1]) = '\0';
					strv[i + j][0] = '.';
					strv[i + j][1] = '\0';
				}
				i += j;
			}
			strv[i][0] = ':';
			strv[i][1] = '\0';
			++i;
		}
		else if (i == 1)
		{
			break;
		}
		free(s);
	}
	return strv;
}