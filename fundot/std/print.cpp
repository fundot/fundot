#include "builtins.h"
#include <iostream>

namespace fundot {

Object* builtin_print(Vector* args) {
    if (args->empty()) {
        return new Null;
    }
    for (std::size_t i{0}, size{args->size()}; i < size; ++i) {
        if (i != 0) {
            std::cout << " ";
        }
        auto obj{args->at(i)};
        auto str{dynamic_cast<String*>(obj)};
        if (str != nullptr) {
            std::cout << str->string_value();
            continue;
        }
        std::cout << obj->to_string();
    }
    return new Null;
}

}
