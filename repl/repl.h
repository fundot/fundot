#ifndef FUNDOT_REPL_REPL_H
#define FUNDOT_REPL_REPL_H

#include "reader.h"
#include "std/builtins.h"
#include <iostream>

namespace fundot {

Object* repl_read_line(Vector* args);

void init_repl();

int repl();

}

#endif
