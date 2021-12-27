#ifndef FUNDOT_REPL_REPL_H
#define FUNDOT_REPL_REPL_H

#include "fundot/std/builtins.h"
#include "reader.h"
#include <iostream>

namespace fundot {

Object* repl_read_line(Vector* args);

void init_repl();

int repl();

}

#endif
