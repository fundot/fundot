#include "builtins.h"

namespace fundot {

Object* builtin_cond(Vector* args) {
    for (std::size_t i{0}; i < args->size(); i += 2) {
        if (!args->at(i)->eval()->equals(new Boolean{false})) {
            return args->at(++i)->eval();
        }
    }
    return new Null;
}

}
