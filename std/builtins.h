#ifndef FUNDOT_STD_BUILTINS_H
#define FUNDOT_STD_BUILTINS_H

#include "addition.h"
#include "subtraction.h"

namespace fundot {

Object* builtin_cond(Vector* args);

Object* builtin_while(Vector* args);

void load_builtins(Object* obj);

}

#endif
