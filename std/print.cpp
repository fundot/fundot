#include "builtins.h"
#include <iostream>

namespace fundot {

Object* builtin_print(Vector* args) {
    if (args->empty()) {
        return new Null;
    }
    auto str{dynamic_cast<String*>(args->at(0))};
    if (str == nullptr) {
        throw Object::Error{"argument of 'print' is not a 'String'"};
    }
    std::cout << str->string_value();
    return new Null;
}

}
