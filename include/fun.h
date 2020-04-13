#ifndef __FUN_H__
#define __FUN_H__

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

#endif