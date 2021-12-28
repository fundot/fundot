#include "builtins.h"

namespace fundot {

Object* builtin_eval(Vector* args) {
    if (args->size() > 1) {
        throw Object::Error{"'eval' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    if (args->empty()) {
        throw Object::Error{"'eval' missing 1 argument: 'expr'"};
    }
    return args->at(0)->eval();
}

}
