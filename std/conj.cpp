#include "builtins.h"

namespace fundot {

Object* builtin_conj(Vector* args) {
    if (args->size() < 2) {
        return new Null;
    }
    auto vec{dynamic_cast<Vector*>(args->at(0))};
    if (vec != nullptr) {
        for (std::size_t i{1}, size{args->size()}; i < size; ++i) {
            vec->push_back(args->at(i));
        }
        return vec;
    }
    auto lst{dynamic_cast<List*>(args->at(0))};
    if (lst != nullptr) {
        for (std::size_t i{1}, size{args->size()}; i < size; ++i) {
            lst->push_back(args->at(i));
        }
        return lst;
    }
    auto set{dynamic_cast<Set*>(args->at(0))};
    if (set != nullptr) {
        for (std::size_t i{1}, size{args->size()}; i < size; ++i) {
            set->insert(args->at(i));
        }
        return set;
    }
    throw Object::Error{"1st argument of 'conj' is not conjoinable"};
}

}
