#include "builtins.h"
#include <iostream>

namespace fundot {

Object* builtin_print(Vector* args) {
    if (args->empty()) {
        throw Object::Error{"'print' missing 1 argument: 'obj'"};
    }
    if (args->size() > 1) {
        throw Object::Error{"'read_line' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    auto obj{args->at(0)};
    auto str{dynamic_cast<String*>(obj)};
    if (str != nullptr) {
        std::cout << str->string_value();
    } else {
        std::cout << obj->to_string();
    }
    return new Null;
}

}
