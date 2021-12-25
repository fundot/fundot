#ifndef FUNDOT_STD_BUILTINS_H
#define FUNDOT_STD_BUILTINS_H

#include "core/boolean.h"
#include "core/function.h"
#include "core/null.h"
#include "core/number.h"
#include "core/object.h"
#include "core/pair.h"
#include "core/parser.h"
#include "core/quote.h"
#include "core/set.h"
#include "core/string.h"
#include "core/symbol.h"
#include "core/vector.h"

namespace fundot {

Object* builtin_cond(Vector* args);

Object* builtin_while(Vector* args);

Object* builtin_add(Vector* args);

void load_builtins(Object* obj);

}

#endif
