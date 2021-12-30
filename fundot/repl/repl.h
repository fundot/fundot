#ifndef FUNDOT_REPL_REPL_H
#define FUNDOT_REPL_REPL_H

#include "fundot/std/builtins.h"
#include "reader.h"

namespace fundot {

class ReadEvalPrintLoop {
public:
    ReadEvalPrintLoop();

    void operator()();

private:
    static Object* read_line(Vector* args);
};

}

#endif
