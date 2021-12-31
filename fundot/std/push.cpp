#include "builtins.h"

namespace fundot {

Object* builtin_push(Vector* args) {
    if (args->empty()) {
        throw Object::Error{"'push' missing 2 arguments: 'item' and 'coll'"};
    }
    if (args->size() < 2) {
        throw Object::Error{"'push' missing 1 argument: 'coll'"};
    }
    auto coll{args->at(1)};
    auto vec{dynamic_cast<Vector*>(coll)};
    if (vec != nullptr) {
        vec->push_back(args->at(0));
        return vec;
    }
    auto lst{dynamic_cast<List*>(coll)};
    if (lst != nullptr) {
        lst->push_back(args->at(0));
        return lst;
    }
    throw Object::Error{
        "second argument of 'push' is neither a 'Vector' nor a 'List'"};
}

}
