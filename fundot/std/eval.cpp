#include "builtins.h"

namespace fundot {

Object* builtin_eval(Vector* args) {
    if (args->size() > 1) {
        throw Object::Error{"'read_line' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    if (args->empty()) {
        throw Object::Error{"'read_line' missing 1 argument: 'expr'"};
    }
    return args->at(0)->eval();
}

}
