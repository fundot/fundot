#include "builtins.h"
#include <iostream>

namespace fundot {

Object* builtin_read_line(Vector* args) {
    if (args->size() > 1) {
        throw Object::Error{"'read_line' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    if (args->size() == 1) {
        builtin_print(args);
    }
    std::string input;
    std::cin >> input;
    return new String{input};
}

}
