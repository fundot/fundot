#include "builtins.h"

namespace fundot {

Object* builtin_while(Vector* args) {
    while (!args->at(0)->eval()->equals(new Boolean{false})) {
        for (std::size_t i{0}, size{args->size()}; i < size; ++i) {
            args->at(i)->eval();
        }
    }
    return new Null;
}

}
