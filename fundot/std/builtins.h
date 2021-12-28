#ifndef FUNDOT_STD_BUILTINS_H
#define FUNDOT_STD_BUILTINS_H

#include "addition.h"
#include "division.h"
#include "equal_to.h"
#include "greater_than.h"
#include "greater_than_or_equal_to.h"
#include "less_than.h"
#include "less_than_or_equal_to.h"
#include "logical_and.h"
#include "logical_not.h"
#include "logical_or.h"
#include "modulo.h"
#include "multiplication.h"
#include "not_equal_to.h"
#include "subtraction.h"
#include "unary_minus.h"
#include "unary_plus.h"

namespace fundot {

Object* builtin_cond(Vector* args);

Object* builtin_let(Vector* args);

Object* builtin_while(Vector* args);

Object* builtin_conj(Vector* args);

Object* builtin_count(Vector* args);

Object* builtin_eval(Vector* args);

Object* builtin_load(Vector* args);

Object* builtin_print(Vector* args);

Object* builtin_read_line(Vector* args);

void load_builtins(Object* obj);

}

#endif
