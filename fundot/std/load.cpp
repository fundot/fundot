#include "builtins.h"
#include <fstream>

namespace fundot {

Object* builtin_load(Vector* args) {
    if (args->size() > 1) {
        throw Object::Error{"'load' takes 1 argument but "
                            + std::to_string(args->size()) + " were given"};
    }
    if (args->empty()) {
        throw Object::Error{"'load' missing 1 argument: 'path'"};
    }
    auto str{dynamic_cast<String*>(args->at(0))};
    auto path{str->string_value()};
    if (str == nullptr) {
        throw Object::Error{"argument of 'load' is not a 'String'"};
    }
    std::ifstream file{path};
    if (!file.is_open()) {
        throw Object::Error{"failed to open '" + path + '\''};
    }
    std::string expr{std::istreambuf_iterator<char>(file),
                     std::istreambuf_iterator<char>()};
    auto context{Object::get_local_context()};
    auto parser{dynamic_cast<Parser*>(context->get(new Symbol{"__parser__"}))};
    if (parser == nullptr) {
        throw Object::Error{"'__parser__' is not a 'Parser'"};
    }
    parser->parse(expr)->eval();
    return new Null;
}

}
