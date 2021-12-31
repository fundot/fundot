#include "builtins.h"

namespace fundot {

Object* builtin_pop(Vector* args) {
    if (args->empty()) {
        throw Object::Error{"'eval' missing 1 argument: 'coll'"};
    }
    auto coll{args->at(0)};
    auto vec{dynamic_cast<Vector*>(coll)};
    if (vec != nullptr) {
        if (vec->empty()) {
            throw Object::Error{"cannot pop empty 'Vector'"};
        }
        vec->pop_back();
        return vec;
    }
    auto lst{dynamic_cast<List*>(coll)};
    if (lst != nullptr) {
        if (lst->empty()) {
            throw Object::Error{"cannot pop empty 'List'"};
        }
        lst->pop_back();
        return lst;
    }
    throw Object::Error{"first argument of 'pop' is not popable"};
}

}
