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
        auto back{vec->at(vec->size() - 1)};
        vec->pop_back();
        return back;
    }
    auto lst{dynamic_cast<List*>(coll)};
    if (lst != nullptr) {
        if (lst->empty()) {
            throw Object::Error{"cannot pop empty 'List'"};
        }
        auto back{vec->at(vec->size() - 1)};
        lst->pop_back();
        return back;
    }
    throw Object::Error{"first argument of 'pop' is not popable"};
}

}
