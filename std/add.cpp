#include "builtins.h"

namespace fundot {

Object* builtin_add(Vector* args) {
    auto first{dynamic_cast<Number*>(args->at(0))};
    if (first == nullptr) {
        throw Object::Error{"first argument of 'add' is not a 'Number'"};
    }
    auto second{dynamic_cast<Number*>(args->at(1))};
    if (second == nullptr) {
        throw Object::Error{"second argument of 'add' is not a 'Number'"};
    }
    if (typeid(*first) == typeid(Integer)
        && typeid(*second) == typeid(Integer)) {
        return new Integer{first->int_value() + second->int_value()};
    }
    return new Float{first->double_value() + second->double_value()};
}

}
