#include "builtins.h"

namespace fundot {

Object* builtin_count(Vector* args) {
    if (args->size() > 1) {
        throw Object::Error{"'count' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    auto coll{args->at(0)};
    auto vec{dynamic_cast<Vector*>(coll)};
    if (vec != nullptr) {
        return new Integer{static_cast<int>(vec->size())};
    }
    auto lst{dynamic_cast<List*>(coll)};
    if (lst != nullptr) {
        return new Integer{static_cast<int>(lst->size())};
    }
    auto set{dynamic_cast<Set*>(coll)};
    if (set != nullptr) {
        return new Integer{static_cast<int>(set->size())};
    }
    auto str{dynamic_cast<String*>(coll)};
    if (str != nullptr) {
        return new Integer{static_cast<int>(str->size())};
    }
    throw Object::Error{"argument of 'count' is not countable"};
}

}
