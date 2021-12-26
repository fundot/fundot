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
    auto s{str->to_string()};
    std::cout << s.substr(1, s.length() - 2);
    return new Null;
}

}
