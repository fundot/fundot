#include "builtins.h"
#include <iostream>

namespace fundot {

Object* builtin_read(Vector* args) {
    if (!args->empty()) {
        throw Object::Error{"'read' takes no argument but more were given"};
    }
    std::string input;
    std::getline(std::cin, input);
    auto context{Object::get_local_context()};
    auto parser{dynamic_cast<Parser*>(context->get(new Symbol{"__parser__"}))};
    if (parser == nullptr) {
        throw Object::Error{"'__parser__' is not a 'Parser'"};
    }
    return dynamic_cast<List*>(parser->parse(input))->front();
}

}
