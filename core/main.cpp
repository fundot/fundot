#include "parser.h"
#include <iostream>

using namespace fundot;

int main() {
    auto scope{new Set};
    Object::set_scope(scope);
    Object::add_root(scope);
    auto parser{new Parser};
    scope->set(new Symbol{"__parser__"}, parser);
    for (;;) {
        try {
            std::cout << "> ";
            std::string input;
            if (!std::getline(std::cin, input)) {
                break;
            }
            std::cout << parser->parse(input)->eval()->to_string() << '\n';
        } catch (Object::Error& error) {
            std::cerr << "Exception: " << error.what() << '\n';
        }
        Object::collect();
    }
    return 0;
}
