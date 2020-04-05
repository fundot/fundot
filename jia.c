#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_SIZE 64
#define BUFFER_SIZE 256
#define FUN_MAP_SIZE 257
#define MAX_ARGC 16
#define MAX_FUN_BODY_SIZE 65536

#define PRINTRUNNING printf("Running..\n");

int int_hash(int sz, int i);
int str_hash(int sz, char* s);
char* get_last_char(char* s);
int str_info(char* s);
int end_dot_count(char* s);

typedef struct fun {
    char* name;
    int argc;
    char** argv;
    int bodyc;
    char** body;
} fun;

fun* construct_fun(char** strv);
void destroy_fun(fun* f);

typedef struct fun_map {
    fun* funs;
    int size;
} fun_map;

fun_map* construct_fun_map(int sz);
void destroy_fun_map(fun_map* fm);
int fun_map_insert(fun_map* fm, fun* f);
int first_upper_index(char** strv);
void destroy_strv(char** strv);
char** eval(char** strv);

fun_map* global_fun_map;

int main(int argc, char** argv) {
    global_fun_map = construct_fun_map(FUN_MAP_SIZE);
    printf("Jia is here to help..\n");
    for (;;) {
	int start_word_count = 0, end_word_count = 0, i = 0;
	char** strv = malloc(BUFFER_SIZE * sizeof(char*));
	while (start_word_count != end_word_count || start_word_count == 0) {
	    char* s = malloc(WORD_SIZE * sizeof(char));
	    scanf("%s", s);
            strv[i] = malloc(WORD_SIZE * sizeof(char));
	    strcpy(strv[i++], s);
	    if (str_info(s) == 0) {
		++start_word_count;
		if (*get_last_char(s) == '.') {
		    ++end_word_count;
		}
	    } else if (str_info(s) == 1) {
		end_word_count += end_dot_count(s);
		int j;
		for (j = 0; j < end_dot_count(s); ++j) {
		    *get_last_char(strv[i - 1]) = '\0';
		    strv[i + j] = malloc(WORD_SIZE * sizeof(char));
		    strv[i + j][0] = '.';
		    strv[i + j][1] = '\0';
		}
		i += j;
	    } else if (str_info(s) == 2) {
		*get_last_char(strv[i - 1]) = '\0';
		strv[i] = malloc(WORD_SIZE * sizeof(char));
		strv[i][0] = ':';
		strv[i][1] = '\0';
		++i;
	    } else if (i == 1) {
		break;
	    }
	    free(s);
	}
	char** new_strv = eval(strv);
	printf("%s\n", new_strv[0]);
	destroy_strv(strv);
	destroy_strv(new_strv);
    }
    destroy_fun_map(global_fun_map);
    return 0;
}

int int_hash(int sz, int i) {
    return i % sz;
}

int str_hash(int sz, char* s) {
    int sum = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
	sum += s[i];
    }
    return int_hash(sz, sum);
}

char* get_last_char(char* s) {
    int i = 0;
    while (s[i] != '\0') {
	if (s[i + 1] == '\0') {
	    return &s[i];
	}
	++i;
    }
    return NULL;
}

int str_info(char* s) {
    if (isupper(s[0])) {
	return 0;
    } else if (*get_last_char(s) == '.') {
	return 1;
    } else if (*get_last_char(s) == ':') {
	return 2;
    }
    return -1;
}

int end_dot_count(char* s) {
    int i = 0;
    while (s[i++] != '\0');
    i -= 2;
    int count = 0;
    while (i >= 0 && s[i--] == '.') {
	++count;
    }
    return count;
}

fun* construct_fun(char** strv) {
    fun* f = malloc(sizeof(fun));
    f->name = malloc(WORD_SIZE * sizeof(char));
    int i = 0;
    strcpy(f->name, strv[i++]);
    f->argv = malloc(MAX_ARGC * sizeof(char*));
    while (i < MAX_ARGC + 1) {
	f->argv[i - 1] = malloc(WORD_SIZE * sizeof(char));
	strcpy(f->argv[i - 1], strv[i]);
	if (str_info(strv[i]) == 2) {
	    break;
	}
	++i;
    } 
    f->argc = i++;
    f->body = malloc(MAX_FUN_BODY_SIZE * sizeof(char*));
    int j = 0;
    while (j < MAX_FUN_BODY_SIZE) {
	f->body[j] = malloc(WORD_SIZE * sizeof(char));
	strcpy(f->body[j], strv[i]);
	if (str_info(strv[i]) == 1) {
	    break;
	}
	++i;
	++j;
    }
    f->bodyc = j;
    return f;
}

void destroy_fun(fun* f) {
    free(f->name);
    for (int i = 0; i < f->argc; ++i) {
	free(f->argv[i]);
    }
    free(f->argv);
    for (int i = 0; i < f->bodyc; ++i) {
	free(f->body[i]);
    }
    free(f->body);
    free(f);
}

fun_map* construct_fun_map(int sz) {
    fun_map* fm = malloc(sizeof(fun_map));
    fm->size = sz;
    fm->funs = malloc(fm->size * sizeof(fun));
    return fm;
}

int fun_map_insert(fun_map* fm, fun* f) {
    int i = str_hash(fm->size, f->name);
    fm->funs[i] = *f;
    return 0;
}

int first_upper_index(char** strv) {
    int i = 0;
    while (*get_last_char(strv[i]) != '.') {
	if (str_info(strv[i]) == 0) {
	    return i;
	}
	++i;
    }
    return -1;
}

void destroy_strv(char** strv) {
    if (str_info(strv[0]) != 0) {
	free(strv[0]);
	free(strv);
	return;
    }
    int start_word_count = 0, end_word_count = 0, i = 0;
    while (start_word_count > end_word_count || start_word_count == 0) {
	int stri = str_info(strv[i]);
	if (stri == 0) {
	    ++start_word_count;
	} else if (*get_last_char(strv[i]) == '.') {
	    ++end_word_count;
	}
	free(strv[i++]);
    }
    free(strv);
}

char** eval(char** strv) {
    char** new_strv = malloc(BUFFER_SIZE * sizeof(char*));
    if (strcmp(strv[0], "Exit.") == 0) {
	exit(0);
    }
    int start_word_count = 0, end_word_count = 0, i = 0;
    while (start_word_count > end_word_count || start_word_count == 0) {
	int stri = str_info(strv[i]);
	if (stri == 0) {
	    ++start_word_count;
	} else if (stri == 1) {
	    ++end_word_count;
	} else if (i == 0) {
	    break;
	}
        if (global_fun_map->funs[str_hash(global_fun_map->size, strv[i])].name != NULL) {
	    fun* f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[i])];
	    if (f->argc == 1) {
		for (int j = 0; j < f->bodyc; ++j) {
		    strcpy(strv[i], f->body[j]);
		}
	    }
	}
	++i;
    }
    if (str_info(strv[0]) == 0 && first_upper_index(strv + 1) != -1) {
	int start_word_count = 0, end_word_count = 0, i = 0, strc = 0;
	while (start_word_count > end_word_count || start_word_count == 0) {
	    int stri = str_info(strv[i]);
	    if (stri == 0) {
		++start_word_count;
		if (start_word_count != 1) {
		    int swc = 0, ewc = 0, j = 0;
		    char** sv = malloc(BUFFER_SIZE * sizeof(char*));
		    while (swc > ewc || swc == 0) {
			int si = str_info(strv[i]);
			if (si == 0) {
			    ++swc;
			} else if (si == 1) {
			    ewc += end_dot_count(strv[i]);
			    if (swc <= ewc) {
				++end_word_count;
			    }
			}
			sv[j] = malloc(WORD_SIZE * sizeof(char));
			strcpy(sv[j++], strv[i++]);
		    }
		    --i;
		    new_strv[strc] = malloc(WORD_SIZE * sizeof(char));
		    strcpy(new_strv[strc++], eval(sv)[0]);
		    destroy_strv(sv);
		} else {
		    new_strv[strc] = malloc(WORD_SIZE * sizeof(char));
		    strcpy(new_strv[strc++], strv[i]);
		    ++i;
		    continue;
		}
	    } else if (stri == 1) {
		++end_word_count;
	    } else {
		new_strv[strc] = malloc(WORD_SIZE * sizeof(char));
		strcpy(new_strv[strc++], strv[i]);
	    }
	    ++i;
	}
        if (str_info(new_strv[strc - 1]) != 1) {
	    *(get_last_char(new_strv[strc - 1]) + 1) = '.';
	    *(get_last_char(new_strv[strc - 1]) + 1) = '\0';
	}
	return eval(new_strv);
    } else if (strcmp(strv[0], "Def") == 0) {
	fun_map_insert(global_fun_map, construct_fun(strv + 1));
        new_strv[0] = malloc(WORD_SIZE * sizeof(char*));
	strcpy(new_strv[0], strv[1]);
	return new_strv;
    } else if (strcmp(strv[0], "Add") == 0) {
	int first = strv[1][0], second = strv[2][0];
	new_strv[0] = malloc(WORD_SIZE * sizeof(char));
	new_strv[0][0] = first + second - '0';
	new_strv[0][1] = '\0';
	return new_strv;
    } else if (global_fun_map->funs[str_hash(global_fun_map->size, strv[0])].name != NULL) {
        fun* f = &global_fun_map->funs[str_hash(global_fun_map->size, strv[0])];
	if (f->argc == 1 && f->bodyc == 1) {
	    free(new_strv);
	    return f->body;
	}
    } else {
	free(new_strv);
	return strv;
    }
    return NULL;
}


